from MakerPlayground.Devices.MP_Device import MP_Device
import Adafruit_DHT as dht
import time

class MP_DHT22(MP_Device):
    
    timeout = 0.03

    def __init__(self, pin):

        self.pin = pin
        self.humid = 0
        self.celcius = 0;
        self.nextReading = 0

    def update(self, currentTime):
        if currentTime >= self.nextReading:
            self.nextReading = currentTime + 0.050
            self.humid, self.celcius = dht.read_retry(dht.DHT22, self.pin, retries=2, delay_seconds=1)
            
            # handle case that there is error while reading
            if self.humid is None and self.celcius is None:
                self.humid = self.celcius = 0

    def getStatus(self):
        return "humid = {0}%,  temp = {1}C".format(self.humid, self.celcius)

    def getTemperature(self):
        return self.celcius

    def getHumidity(self):
        return self.humid;