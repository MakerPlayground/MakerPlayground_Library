# from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import Adafruit_SSD1306

from PIL import Image, ImageFont, ImageDraw

# class MP_OLED_SSD1306_128x64(MP_Device):
class MP_OLED_SSD1306_128x64():

    MAX_ENTRY_COUNT = 10
    SCREEN_WIDTH = 128
    SCREEN_HEIGHT = 64

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

        self.entries = [{
            'message': '',
            'size': 1
        }] * MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT

        self.entryWithPositionCount = 0

        self.entriesWithPosition = [{
            'x': -1,
            'y': -1,
            'message': '',
            'size': 1,
        }] * MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT

    def _show(self):
        line_height = 20
        image = Image.new('1', (self.disp.width, self.disp.height))
        draw = ImageDraw.Draw(image)
        currentY = 0
        for entry in self.entries:
            if entry['message'] != '':
                draw.text((0, currentY), entry['message'], fill=1)
            currentY += (entry['size'] * line_height)
        for entry in self.entriesWithPosition:
            if entry['message'] != '':
                draw.text((entry.x, entry.y), entry['message'], fill=1)
        self.disp.image(image)
        self.disp.display()

    def showTextAtLine(self, line, text, size, color):
        line_index = line - 1
        if line_index >= 0 and line_index < MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT:
            size_dict = {
                'Small': 1,
                'Medium': 2,
                'Large': 3,
            }
            self.entries[line_index]['message'] = str(text)
            self.entries[line_index]['size'] = size_dict[size]
            self._show()

    def showTextAtPosition(self, x, y, text, size, color):
        if x >= 0 and x < MP_OLED_SSD1306_128x64.SCREEN_WIDTH and y >= 0 and y < MP_OLED_SSD1306_128x64.SCREEN_HEIGHT:
            storingIndex = -1
            for i in range(self.entryWithPositionCount):
                if self.entriesWithPosition[i].x == x and self.entriesWithPosition[i].y == y:
                    storingIndex = i
                    break
            if self.entryWithPositionCount == MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT:
                return
            
            if storingIndex == -1:
                storingIndex = self.entryWithPositionCount
                self.entryWithPositionCount += 1
            
            size_dict = {
                'Small': 1,
                'Medium': 2,
                'Large': 3,
            }
            self.entriesWithPosition[storingIndex]['size'] = size_dict[size]
            self.entriesWithPosition[storingIndex]['message'] = text
            self.entriesWithPosition[storingIndex]['x'] = x
            self.entriesWithPosition[storingIndex]['y'] = y
            self.show()

    def showNumberAtLine(self, line, label, value, decimalPlaces, size, color):
        value_str = "{:.{}f}".format(value, decimalPlaces)
        temp = str(label).replace('/value/', value_str, 1)
        self.showTextAtLine(line, temp, size, color)

    def showNumberAtPosition(self, x, y, label, value, decimalPlaces, size, color):
        value_str = "{:.{}f}".format(value, decimalPlaces)
        temp = str(label).replace('/value/', value_str, 1)
        self.showTextAtPosition(x, y, temp, size, color)

    def clearLine(self, line):
        self.entries[line-1]['message'] = ''

    # def showText(self, line, text):
    #     self.entries[line-1] = str(text)
    #     self._show()

    # def showNumber(self, line, label, value):
    #     self.entries[line-1] = str(label).replace("/value/", "{:.2f}".format(value), 1)
    #     self._show()

    def clearScreen(self):
        self.entries = [{
            'message': '',
            'size': 1
        }] * MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT

        self.entriesWithPosition = [{
            'x': -1,
            'y': -1,
            'message': '',
            'size': 1,
        }] * MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT
        
        self._show()

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "Data on screen: {0}, {1}".format(self.entries, self.entriesWithPosition)
    
    def _dispose(self):
        self.clearScreen()