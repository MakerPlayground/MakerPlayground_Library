import MakerPlayground as mp

class MP_LED_AL:
    def __init__(self, pin):
        self.pin = pin
        self.brightness = 100.0

    def init(self):
        if mp.pinMode(self.pin, mp.GPIO_DIR.OUT, enable_pwm=True):
            return mp.ERR_OK
        else:
            return mp.ERR_CONFIG_DEVICE

    def update(self, currentTime):
        pass

    def printStatus(self):
        pass

    def on(self, brightness):
        mp.analogWrite(self.pin, 100 - brightness)

    def off(self):
        mp.analogWrite(self.pin, 100)