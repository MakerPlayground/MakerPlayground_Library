import time
import pigpio
import netifaces
import asyncio
import websockets

class Expr:
    def __init__(self, fn = lambda: None, value: float = 0.0, interval: float = 0.0, latestUpdateTime: float = 0):
        self.fn = fn
        self.value = value
        self.interval = interval
        self.latestUpdateTime = latestUpdateTime

def get_ipv4_list():
    ipv4_list = []
    for interface in netifaces.interfaces():
        for link in netifaces.ifaddresses(interface)[netifaces.AF_INET]:
            ipv4_list.append(link['addr'])
    return ipv4_list

def create_receive_cmd(do_action_fn):
    if do_action_fn is None:
        async def receive_cmd(websocket, path):
            async for message in websocket:
                pass
        return receive_cmd
    else:
        async def receive_cmd(websocket, path):
            async for message in websocket:
                do_action_fn(message)
        return receive_cmd
    
def create_send_cmd(message_fn, message_delay):
    if message_fn is None:
        async def send_values(websocket, path):
            pass
        return send_values
    else:
        async def send_values(websocket, path):
            while True:
                await websocket.send(message_fn())
                await asyncio.sleep(message_delay)
        return send_values

def create_ws_handler(do_action_fn, message_fn, message_delay):
    async def handler(websocket, path):
        consumer_task = asyncio.ensure_future(create_receive_cmd(do_action_fn)(websocket, path))
        producer_task = asyncio.ensure_future(create_send_cmd(message_fn, message_delay)(websocket, path))
        done, pending = await asyncio.wait([consumer_task, producer_task], return_when=asyncio.FIRST_COMPLETED)
        for task in pending:
            task.cancel()
    return handler

class InteractiveServer:

    m_delay = 0.1      # message log delay (second)

    @staticmethod
    def start(do_action_fn=None, message_fn=None):
        for ipv4 in get_ipv4_list():
            print(f"running on {ipv4}:6213")
            asyncio.get_event_loop().run_until_complete(websockets.serve(create_ws_handler(do_action_fn, message_fn, InteractiveServer.m_delay), ipv4, 6213))
        asyncio.get_event_loop().run_forever()

class MPRunner:

    m_delay = 1      # message log delay (second)

    @staticmethod
    def start(main_fn, message_log_fn):
        for ipv4 in get_ipv4_list():
            asyncio.get_event_loop().run_until_complete(websockets.serve(create_ws_handler(None, message_log_fn, MPRunner.m_delay), ipv4, 6213))
        asyncio.get_event_loop().run_until_complete(main_fn())
        asyncio.get_event_loop().run_forever()

class MP:
    currentNode = lambda: None
    devices = {}
    expressions = {}
    tasks = {}
    
    latestLogTime = 0.
    currentTime = 0.

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
                try:
                    device._dispose()
                except:
                    pass

    @staticmethod
    def constrain(data, min_value, max_value):
        return min(max(data, min_value), max_value)

    @staticmethod
    def map(x: float, in_min: float, in_max: float, out_min: float, out_max: float):
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# if __name__ == '__main__':
#     def do_action(message):
#         print(message)
#     def gen_message():
#         ret_val = "'aaaa'"
#         for device_name, device in MP.devices.items():
#             ret_val += "[[{0}]] {1}\0".format(device_name, device.getStatus())
#         print(ret_val)
#         return ret_val
#     async def do_something():
#         pass
#     async def main():
#         while(True):
#             await asyncio.sleep(0)
#             MP.update()
#             time.sleep(1)
#             print(444)

#     MPRunner.start(main, gen_message)
#     # # TODO: allow only one interactive session, close the connection after the websocket is closed.
#     # InteractiveServer.start(do_action_fn=do_action, message_fn=gen_message)