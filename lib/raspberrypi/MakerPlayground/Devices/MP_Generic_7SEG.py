from abc import ABC, abstractmethod
from .MP_Device import MP_Device

class MP_Generic_7SEG(MP_Device):

    @abstractmethod
    def showData(self, data: float):
        raise NotImplementedError("Device is required to declare the 'showData' method")

    @abstractmethod
    def showTwoIntWithColon(self, beforeColon: int, afterColon: int):
        raise NotImplementedError("Device is required to declare the 'showTwoIntWithColon' method")