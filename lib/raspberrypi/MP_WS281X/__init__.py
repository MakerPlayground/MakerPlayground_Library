from MakerPlayground.Devices.MP_Device import MP_Device
from rpi_ws281x import *

class MP_WS281X(MP_Device):

    def __init__(self, pin, led_count=1):

        LED_FREQ_HZ = 800000
        LED_DMA = 5
        LED_INIT_BRIGHTNESS = 255
        LED_INVERT = False

        self.pin = pin
        self.led_count = led_count
        self.brightness = 0.0
        self.colors = [Color(255, 255, 255)] # initial color is white
        self.strip = Adafruit_NeoPixel(led_count, pin, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_INIT_BRIGHTNESS)
        self.strip.begin()
        
    def on(self, red, green, blue, brightness):
        red, green, blue = int(red), int(green), int(blue)
        self.stripOn([Color(red, green, blue)], brightness)

    def stripOn(self, colors, brightness):
        self.colors = colors
        self.brightness = brightness
        for i, color in enumerate(colors):
            self.strip.setPixelColor(i, color)
        self.strip.setBrightness(int(brightness * 2.55))  # convert from percent to 0-255
        self.strip.show()

    def off(self):
        self.strip.setBrightness(0)  # convert from percent to 0-255
        self.strip.show()

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "brightness = {0:.2f}, color = {1}".format(self.brightness, self.colors)

    def _dispose(self):
        self.off()