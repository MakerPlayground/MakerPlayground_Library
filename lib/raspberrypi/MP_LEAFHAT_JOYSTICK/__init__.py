from MakerPlayground.Devices.MP_Device import MP_Device
from enum import Enum
import pigpio
import time

class MP_LEAFHAT_JOYSTICK(MP_Device):

    def __init__(self, pin6, pin17, pin18, pin22, pin23):
        self.pinUp = pin6
        self.pinLeft = pin17
        self.pinRight = pin18
        self.pinMiddle = pin22
        self.pinDown = pin23

        self.pi = pigpio.pi()

        self.pi.set_mode(self.pinUp, pigpio.INPUT)
        self.pi.set_mode(self.pinLeft, pigpio.INPUT)
        self.pi.set_mode(self.pinRight, pigpio.INPUT)
        self.pi.set_mode(self.pinMiddle, pigpio.INPUT)
        self.pi.set_mode(self.pinDown, pigpio.INPUT)

        self.pi.set_pull_up_down(self.pinUp, pigpio.PUD_UP)
        self.pi.set_pull_up_down(self.pinLeft, pigpio.PUD_UP)
        self.pi.set_pull_up_down(self.pinRight, pigpio.PUD_UP)
        self.pi.set_pull_up_down(self.pinMiddle, pigpio.PUD_UP)
        self.pi.set_pull_up_down(self.pinDown, pigpio.PUD_UP)
 
        self.checkpoint = time.time()

    def update(self, currentTime):
        pass

    def getStatus(self):
        if self.isUpPress():
            return "up pressed"
        if self.isLeftPress():
            return "left pressed"
        if self.isRightPress():
            return "right pressed"
        if self.isDownPress():
            return "down pressed"
        if self.isMiddlePress():
            return "middle pressed"
        if self.isAllRelease():
            return "all release"
        return ""


    def isUpPress(self):
        return self.pi.read(self.pinUp) == 0

    def isLeftPress(self):
        return self.pi.read(self.pinLeft) == 0

    def isRightPress(self):
        return self.pi.read(self.pinRight) == 0

    def isDownPress(self):
        return self.pi.read(self.pinDown) == 0

    def isMiddlePress(self):
        return self.pi.read(self.pinMiddle) == 0


    def isUpRelease(self):
        return self.pi.read(self.pinUp) == 1

    def isLeftRelease(self):
        return self.pi.read(self.pinLeft) == 1

    def isRightRelease(self):
        return self.pi.read(self.pinRight) == 1

    def isDownRelease(self):
        return self.pi.read(self.pinDown) == 1

    def isMiddleRelease(self):
        return self.pi.read(self.pinMiddle) == 1


    def isAllRelease(self):
        release_list = [self.isUpRelease(), self.isDownRelease(), self.isLeftRelease(), self.isRightRelease(), self.isMiddleRelease()]
        return all(release_list)