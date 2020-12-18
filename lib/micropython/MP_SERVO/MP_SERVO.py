import MakerPlayground as mp

class MP_SERVO:
    def __init__(self, pin):
        self.pin = pin

    def init(self):
        if mp.pinMode(self.pin, mp.GPIO_DIR.OUT, enable_pwm=True, pwm_freq=50):
            return mp.ERR_OK
        else:
            return mp.ERR_CONFIG_DEVICE

    def update(self, currentTime):
        pass

    def printStatus(self):
        pass

    def moveto(self, degree):
        mp.analogWrite(self.pin, (degree / 180.0 * 10.0) + 2.5)
