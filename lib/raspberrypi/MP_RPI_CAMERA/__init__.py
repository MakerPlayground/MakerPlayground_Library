from MakerPlayground.Devices.MP_Device import MP_Device
import time
import io
from picamera import PiCamera
from PIL import Image

class MP_RPI_CAMERA(MP_Device):

    def __init__(self, max_fps):
        self.last_capture_time = 0
        self.min_seconds_wait_per_capture = 1.0 / max_fps
        self.stream = io.BytesIO()
        self.image = None

    def update(self, currentTime):
        if currentTime - self.last_capture_time < self.min_seconds_wait_per_capture:
            return
        self.stream.seek(0)
        with PiCamera(sensor_mode=2) as camera:
            camera.capture(self.stream, format='jpeg')
        # "Rewind" the stream to the beginning so we can read its content
        self.stream.seek(0)
        self.image = Image.open(self.stream)
        self.last_capture_time = currentTime

    def getStatus(self):
        return "Image was captured on {0}".format(self.last_capture_time)

    def getImage(self):
        return self.image
