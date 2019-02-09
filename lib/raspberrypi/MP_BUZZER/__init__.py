from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import time

class MP_BUZZER(MP_Device):
    
    def __init__(self, pin):
        self.pi = pigpio.pi()
        self.pi.set_mode(pin, pigpio.OUTPUT)
        self.pi.set_PWM_range(pin, 100)
        self.pin = pin
        self.stop_time = 0
        self.text_status = "Device is ready"

    def update(self, currentTime):
        if currentTime >= self.stop_time:
            self.pi.set_PWM_dutycycle(self.pin, 0)

    def getStatus(self):
        return self.text_status

    def beep(self):
        self.text_status = "Last action: beep"
        self.pi.set_PWM_frequency(self.pin, 5000)
        self.pi.set_PWM_dutycycle(self.pin, 80)
        time.sleep(0.050)
        self.pi.set_PWM_dutycycle(self.pin, 0)

    def play(self, frequency, duration):
        self.text_status = "Last action: play sound {0} Hz for {1} second".format(frequency, duration)
        self.pi.set_PWM_frequency(self.pin, int(frequency))
        self.pi.set_PWM_dutycycle(self.pin, 50)
        self.stop_time = time.time() + duration