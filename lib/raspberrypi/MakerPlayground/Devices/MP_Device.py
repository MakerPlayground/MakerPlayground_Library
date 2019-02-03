from abc import ABC, abstractmethod

class MP_Device(ABC):
    errors = ['ok']
    
    @abstractmethod
    def __init__(self, *args, **kwargs):
        pass

    @abstractmethod
    def update(self, currentTime):
        pass

    @abstractmethod
    def getStatus(self):
        pass