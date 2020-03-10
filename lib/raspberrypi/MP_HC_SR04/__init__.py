from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import time

class MP_HC_SR04(MP_Device):
    
    timeout = 0.03

    def __init__(self, trig, echo):
        self.pi = pigpio.pi()
        self.pi.set_mode(trig, pigpio.OUTPUT)
        self.pi.set_mode(echo, pigpio.INPUT)

        self.trig = trig
        self.echo = echo
        self.cm = 0
        self.nextReading = 0;

    def update(self, currentTime):
        if currentTime >= self.nextReading:
            self.nextReading = currentTime + 0.050
            
            # create pulse
            self.pi.write(self.trig, pigpio.LOW)
            time.sleep(0.000002)
            self.pi.write(self.trig, pigpio.HIGH)
            time.sleep(0.000010)
            self.pi.write(self.trig, pigpio.LOW)
            
            beforeTime = time.time()
            startTime = stopTime = 0

            # save startTime
            while self.pi.read(self.echo) == pigpio.LOW:
                startTime = time.time()
                if startTime - beforeTime < 0.3:
                    self.cm = 0
                    return

            # save time of arrival
            while self.pi.read(self.echo) == pigpio.HIGH and stopTime - startTime < MP_HC_SR04.timeout:
                stopTime = time.time()

            interval = stopTime - startTime
            if interval <= MP_HC_SR04.timeout:
                self.cm = (interval * 1000000) / 29 / 2

            if self.cm > 450.0:
                self.cm = 0

    def getStatus(self):
        return "distance (cm.) = {0}".format(self.cm)

    def getDistance(self):
        return self.cm

    def _dispose(self):
        self.pi.stop()