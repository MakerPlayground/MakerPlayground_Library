from machine import Pin
from neopixel import NeoPixel
import MakerPlayground.MakerPlayground as mp

class MP_WS281X_STRIP_GRB:
    def __init__(self, pin, numPixel):
        self.pin = pin
        self.numPixel = int(numPixel)
        self.brightness = 100.0

    def init(self):
        pin = Pin(self.pin, Pin.OUT)
        self.np = NeoPixel(pin, self.numPixel)
        return mp.ERR_OK

    def update(self, currentTime):
        pass

    def printStatus(self):
        pass

    def setColor(self, index, red, green, blue):
        scale = self.brightness / 100.0
        self.np[int(index)-1] = (int(red * scale), int(green * scale), int(blue * scale))
        self.np.write()

    def fillColor(self, startIndex, endIndex, red, green, blue):
        scale = self.brightness / 100.0
        color = (int(red * scale), int(green * scale), int(blue * scale))
        for i in range(int(startIndex), int(endIndex+1)):
            self.np[i-1] = color
        self.np.write()

    def setBrightness(self, brightness):
        if self.brightness != brightness:
            scale = brightness / 100.0
            for i in range(self.numPixel):
                self.np[i] = (int(self.np[i][0] * scale), int(self.np[i][1] * scale), int(self.np[i][2] * scale))
            self.np.write()
        self.brightness = brightness
        pass

    def clear(self):
        color = (0, 0, 0)
        for i in range(self.numPixel):
            self.np[i] = color
        self.np.write()