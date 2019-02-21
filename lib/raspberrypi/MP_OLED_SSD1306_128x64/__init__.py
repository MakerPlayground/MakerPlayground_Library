from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import Adafruit_SSD1306

from PIL import Image, ImageFont, ImageDraw

class MP_OLED_SSD1306_128x64(MP_Device):
    
    def __init__(self):
        RST = 1
        self.pi = pigpio.pi()
        self.pi.set_mode(2, pigpio.ALT0)
        self.pi.set_mode(3, pigpio.ALT0)
        self.pi.stop()

        self.disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)
        self.disp.begin()
        self.disp.clear()
        self.font = ImageFont.load_default()

        self.memory = {}

    def _show(self):
        line_height = 20
        image = Image.new('1', (self.disp.width, self.disp.height))
        draw = ImageDraw.Draw(image)
        for line_number, data in self.memory.items():
            draw.text((0, int(line_number * line_height)), data, fill=1)
        self.disp.image(image)
        self.disp.display()

    def showText(self, line, text):
        self.memory[line-1] = str(text)
        self._show()

    def showNumber(self, line, label, value):
        self.memory[line-1] = str(label).replace("/value/", str(value), 1)
        self._show()

    def clearScreen(self):
        self.memory = {}
        self._show()

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "Data on screen: {0}".format(self.memory)
    
    def _dispose(self):
        self.clearScreen()