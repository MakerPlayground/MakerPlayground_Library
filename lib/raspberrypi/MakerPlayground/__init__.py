import time
import pigpio

MP_LOG_INTERVAL = 1

def constrain(data, min_value, max_value):
    return min(max(data, min_value), max_value)

def map(x: float, in_min: float, in_max: float, out_min: float, out_max: float):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

class Expr:
    def __init__(self, fn = lambda: None, value: float = 0.0, interval: float = 0.0, latestUpdateTime: float = 0):
        self.fn = fn
        self.value = value
        self.interval = interval
        self.latestUpdateTime = latestUpdateTime

class MP:
    currentNode = lambda: None
    devices = {}
    expressions = {}
    tasks = {}
    
    latestLogTime = 0
    currentTime = 0

    @staticmethod
    def update():
        MP.currentTime = time.time()
        for device_name, device in MP.devices.items():
            device.update(MP.currentTime)
        for device_name, task in MP.tasks.items():
            if task is not None:
                for expr in MP.expressions[device_name]:
                    if isinstance(expr, Expr) and MP.currentTime - expr.latestUpdateTime >= expr.interval:
                        expr.value = expr.fn()
                        expr.lastUpdateTime = MP.currentTime
                        task()
        if MP.currentTime - MP.latestLogTime > MP_LOG_INTERVAL:
            for device_name, device in MP.devices.items():
                print("[[{0}]] {1}\0".format(device_name, device.getStatus()))
            MP.latestLogTime = time.time()

    @staticmethod
    def clearExpression(device_name: str, index: int):
        MP.expressions[device_name][index] = None

    @staticmethod
    def setExpression(device_name: str, index: int, fn, interval: float):
        MP.expressions[device_name][index] = Expr(fn, fn(), interval, MP.currentTime)

    @staticmethod
    def setTask(device_name: str, fn):
        MP.tasks[device_name] = fn
        fn()

    @staticmethod
    def unsetTask(device_name: str):
        MP.tasks[device_name] = None

    @staticmethod
    def unsetAllPins():
        pi = pigpio.pi()
        hardware_revision = pi.get_hardware_revision()
        if hardware_revision in [2, 3]:
            pins = [0, 1, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 21, 22, 23, 24, 25]
        elif hardware_revision in [4, 5, 6, 15]:
            pins = [2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 17, 18, 22, 23, 24, 25, 27, 28, 29, 30, 31]
        elif hardware_revision >= 16:
            pins = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]
        else:
            return
        for p in pins:
            pi.set_mode(p, pigpio.INPUT)

    @staticmethod
    def cleanup():
        for device_name, device in MP.devices.items():
            if "_dispose" in dir(device):
                device._dispose()