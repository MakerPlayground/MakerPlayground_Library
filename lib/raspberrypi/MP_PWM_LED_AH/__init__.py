from MakerPlayground.Devices import MP_Generic_LED
import pigpio

class MP_PWM_LED_AH(MP_Generic_LED):
    
    def __init__(self, pin):
        self.pin = pin
        self.brightness = 0
        self.pi = pigpio.pi()
        self.pi.set_mode(self.pin, pigpio.OUTPUT)
        self.pi.set_PWM_frequency(self.pin, 1000)
        self.pi.set_PWM_range(self.pin, 100)
        self.pi.set_PWM_dutycycle(self.pin, 0)

    def on(self, brightness):
        self.brightness = brightness
        self.pi.set_PWM_dutycycle(self.pin, brightness)

    def off(self):
        self.brightness = 0.0
        self.pi.set_PWM_dutycycle(self.pin, 0.0)

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "brightness = {0:.2f}".format(self.brightness)
    
    def _dispose(self):
        self.pi.stop()