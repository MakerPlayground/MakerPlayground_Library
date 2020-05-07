from MakerPlayground.Devices.MP_Device import MP_Device
import time
import io
from picamera import PiCamera
from PIL import Image

class MP_RPI_CAMERA(MP_Device):

    def __init__(self, sensor_mode, max_fps, rotation):
        self.last_capture_time = 0
        self.min_seconds_wait_per_capture = 1.0 / max_fps
        self.stream = io.BytesIO()
        self.image = None
        self.camera = PiCamera(sensor_mode=sensor_mode)
        self.camera.rotation = rotation

    def update(self, currentTime):
        if currentTime - self.last_capture_time < self.min_seconds_wait_per_capture:
            return
        self.stream.seek(0)
        self.camera.capture(self.stream, format='jpeg')
        # "Rewind" the stream to the beginning so we can read its content
        self.stream.seek(0)
        self.image = Image.open(self.stream)
        self.last_capture_time = currentTime

    def getStatus(self):
        return "Image was captured on {0}".format(self.last_capture_time)

    def getImage(self):
        return self.image
