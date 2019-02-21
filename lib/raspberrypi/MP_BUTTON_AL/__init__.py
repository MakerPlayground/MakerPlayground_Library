from MakerPlayground.Devices.MP_Device import MP_Device
from enum import Enum
import pigpio
import time

class State(Enum):
    NOTHING = 1
    PRESSED = 2
    JUST_RELEASE = 3

class MP_BUTTON_AL(MP_Device):

    def __init__(self, pin):
        self.pin = pin
        self.pi = pigpio.pi()

        self.pi.set_mode(pin, pigpio.INPUT)
        self.pi.set_pull_up_down(pin, pigpio.PUD_UP)
 
        self.checkpoint = time.time()
        self.state = State.NOTHING

    def update(self, currentTime):
        if self.state == State.NOTHING and self.isPress():
            self.state = State.PRESSED
        
        if self.state == State.PRESSED and self.isNotPress():
            self.state = State.JUST_RELEASE
            self.checkpoint = currentTime
        
        if self.state == State.JUST_RELEASE and currentTime - self.checkpoint >= 0.150:
            self.state = State.NOTHING

    def getStatus(self):
        return "Button is {0}".format("pressed" if self.isPress() else "not pressed")

    def isPress(self):
        return self.pi.read(self.pin) == 0

    def isPressAndRelease(self):
        if self.state == State.JUST_RELEASE:
            self.state = State.NOTHING
            self.checkpoint = time.time()
            return True
        return False

    def isNotPress(self):
        return self.pi.read(self.pin) == 1