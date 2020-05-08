from MakerPlayground.Devices.MP_Device import MP_Device
import time
import io
from picamera import PiCamera
from PIL import Image

class MP_RPI_CAMERA(MP_Device):

    def __init__(self, sensor_mode, rotation):
        self.stream = io.BytesIO()
        self.image = None
        self.camera = PiCamera(sensor_mode=sensor_mode)
        self.camera.rotation = rotation
        self.generator = self.camera.capture_continuous(self.stream, use_video_port=True, format='jpeg')

    def update(self, currentTime):
        self.stream.truncate()
        self.stream.seek(0)
        next(self.generator)

        self.stream.truncate()
        self.stream.seek(0)
        self.image = Image.open(self.stream)

    def getStatus(self):
        return "Image was captured on {0}".format(self.last_capture_time)

    def getImage(self):
        return self.image

    def _dispose(self):
        self.camera.close()