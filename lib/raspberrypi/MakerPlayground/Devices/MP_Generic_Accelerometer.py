from abc import ABC, abstractmethod
from .MP_Device import MP_Device
import math

class MP_Generic_Accelerometer(MP_Device):
    
    @abstractmethod
    def getAccel_X(self):
        raise NotImplementedError("Device is required to declare the 'getAccel_X' method")

    @abstractmethod
    def getAccel_Y(self):
        raise NotImplementedError("Device is required to declare the 'getAccel_Y' method")
    
    @abstractmethod
    def getAccel_Z(self):
        raise NotImplementedError("Device is required to declare the 'getAccel_Z' method")

    def getAccel_Magnitude(self):
        x2 = self.getAccel_X() * self.getAccel_X()
        y2 = self.getAccel_Y() * self.getAccel_Y()
        z2 = self.getAccel_Z() * self.getAccel_Z()
        return math.sqrt(x2 + y2 + z2)