from abc import ABC, abstractmethod
from .MP_Device import MP_Device

class MP_Generic_LED(MP_Device):
    
    @abstractmethod
    def on(self, brightness: float):
        raise NotImplementedError("Device is required to declare the 'on' method")

    @abstractmethod
    def off(self):
        raise NotImplementedError("Device is required to declare the 'off' method")
