import time
import signal
import functools
import pigpio
import asyncio
import websockets

class Expr:
    def __init__(self, fn = lambda: None, value: float = 0.0, interval: float = 0.0, latestUpdateTime: float = 0):
        self.fn = fn
        self.value = value
        self.interval = interval
        self.latestUpdateTime = latestUpdateTime

class MPInteractive:

    m_delay = 0.1      # message log delay (second)

    update_fn = lambda: None
    message_fn = lambda: ''
    action_fn = lambda msg: None

    @staticmethod
    def log(msg):
        asyncio.get_event_loop().call_soon(functools.partial(print, str(msg), flush=True)) 

    @staticmethod
    async def receive_handler(websocket, path):
        try:
            async for message in websocket:
                asyncio.get_event_loop().call_soon(functools.partial(MPInteractive.action_fn, message)) 
                MPInteractive.log(message)
        except Exception as ex:
            MPInteractive.log(ex)
            MPInteractive.log(f"Receive handler for {websocket.remote_address} is stopped.")

    @staticmethod
    async def send_handler(websocket, path):
        try:
            while True:
                msg = MPInteractive.message_fn()
                await websocket.send(msg)
                await asyncio.sleep(MPInteractive.m_delay)
        except Exception as ex:
            MPInteractive.log(ex)
            MPInteractive.log(f"Send handler for {websocket.remote_address} is stopped.")

    @staticmethod
    async def handler(websocket, path):
        MPInteractive.log(f"New interactive session from {websocket.remote_address}")
        receive_cmd_future = asyncio.ensure_future(MPInteractive.receive_handler(websocket, path))
        send_cmd_future = asyncio.ensure_future(MPInteractive.send_handler(websocket, path))
        _, pending = await asyncio.wait([receive_cmd_future, send_cmd_future], return_when=asyncio.FIRST_COMPLETED)
        for task in pending:
            task.cancel()

    @staticmethod
    async def server(stop):
        async with websockets.serve(MPInteractive.handler, None, 6213) as server:
            await stop
            server.close()
            await server.wait_closed()

    @staticmethod
    async def server_with_main(main_fn):
        loop = asyncio.get_event_loop()
        stop = loop.create_future()

        loop.add_signal_handler(signal.SIGINT, lambda: stop.set_result(None))

        main_future = asyncio.ensure_future(main_fn())
        server_future = asyncio.ensure_future(MPInteractive.server(stop))

        _, pending = await asyncio.wait([main_future, server_future], return_when=asyncio.FIRST_COMPLETED)
        for task in pending:
            task.cancel()

    @staticmethod
    def start(update_fn=None, action_fn=None, message_fn=None):
        if update_fn:
            MPInteractive.update_fn = update_fn
        if action_fn:
            MPInteractive.action_fn = action_fn
        if message_fn:
            MPInteractive.message_fn = message_fn
        asyncio.run(MPInteractive.server_with_main(update_fn))

class MPRunner:

    m_delay = 1      # message log delay (second)
    message_fn = lambda: 'Message is not set yet'

    @staticmethod
    def log(msg):
        asyncio.get_event_loop().call_soon(functools.partial(print, msg, flush=True)) 

    @staticmethod
    async def handler(websocket, path):
        MPRunner.log(f"New monitor connected from {websocket.remote_address}")
        try:
            while True:
                msg = MPRunner.message_fn()
                await websocket.send(msg)
                await asyncio.sleep(MPRunner.m_delay)
        except websockets.exceptions.ConnectionClosedOK:
            MPRunner.log(f"Connection {websocket.remote_address} is closed")

    @staticmethod
    async def device_monitor_server(stop):
        async with websockets.serve(MPRunner.handler, None, 6213) as server:
            await stop
            server.close()
            await server.wait_closed()

    @staticmethod
    async def server_with_main(main_fn):
        loop = asyncio.get_event_loop()
        stop = loop.create_future()

        loop.add_signal_handler(signal.SIGINT, lambda: stop.set_result(None))

        main_future = asyncio.ensure_future(main_fn())
        server_future = asyncio.ensure_future(MPRunner.device_monitor_server(stop))

        _, pending = await asyncio.wait([main_future, server_future], return_when=asyncio.FIRST_COMPLETED)
        for task in pending:
            task.cancel()

    @staticmethod
    def start(main_fn, message_log_fn=None):
        if message_log_fn:
            MPRunner.message_fn = message_log_fn
        asyncio.run(MPRunner.server_with_main(main_fn))

class MP:
    currentNode = lambda: None
    devices = {}
    memory = {}
    expressions = {}
    tasks = {}
    c_args = {}
    
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
        for _, device in MP.devices.items():
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

if __name__ == '__main__':

    def do_action(message):
        print(message)

    def gen_message():
        ret_val = "'test_message: '"
        for device_name, device in MP.devices.items():
            ret_val += "[[{0}]] {1}\0".format(device_name, device.getStatus())
        print(ret_val)
        return ret_val

    async def do_something():
        pass

    async def main():
        while(True):
            await asyncio.sleep(0)
            MP.update()
            print("main is running")

    # MPRunner.start(main, gen_message)
    # MPRunner.start(main)
    # # TODO: allow only one interactive session, close the connection after the websocket is closed.
    MPInteractive.start(update_fn=main, action_fn=do_action, message_fn=gen_message)