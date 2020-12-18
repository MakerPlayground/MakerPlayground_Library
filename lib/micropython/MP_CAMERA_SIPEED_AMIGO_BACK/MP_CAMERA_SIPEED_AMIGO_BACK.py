import sensor, utime
import MakerPlayground as mp
import gc

class MP_CAMERA_SIPEED_AMIGO_BACK:
    UPDATE_INTERVAL = 50

    def __init__(self):
        pass

    def init(self):
        sensor.reset(choice=1)
        sensor.set_pixformat(sensor.YUV422)
        sensor.set_framesize(sensor.QVGA)
        sensor.set_hmirror(1)
        sensor.set_vflip(1)
        sensor.skip_frames(time=2000)

        self.img = None
        self.latestUpdateTime = 0
        return mp.ERR_OK

    def update(self, currentTime):
        if utime.ticks_diff(currentTime, self.latestUpdateTime) > MP_CAMERA_SIPEED_AMIGO_BACK.UPDATE_INTERVAL:
            self.img = sensor.snapshot()
            self.latestUpdateTime = currentTime
            gc.collect()

    def printStatus(self):
        pass

    def getImage(self):
        return self.img