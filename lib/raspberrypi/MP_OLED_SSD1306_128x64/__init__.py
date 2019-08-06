from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import Adafruit_SSD1306
import os.path as path

from PIL import Image, ImageFont, ImageDraw

class MP_OLED_SSD1306_128x64(MP_Device):

    MAX_ENTRY_COUNT = 7
    SCREEN_WIDTH = 128
    SCREEN_HEIGHT = 64

    CHAR_WIDTH_1X = 7
    CHAR_HEIGHT_1X = 12
    ROW_HEIGHT = 9
    
    CURRENT_DIR = path.dirname(path.abspath(__file__))
    FONT_FILE_PATH = path.join(CURRENT_DIR, "FreeMonoBold.ttf")
    FONT_1X = ImageFont.truetype(FONT_FILE_PATH, CHAR_HEIGHT_1X)
    FONT_2X = ImageFont.truetype(FONT_FILE_PATH, 2 * CHAR_HEIGHT_1X)
    FONT_3X = ImageFont.truetype(FONT_FILE_PATH, 3 * CHAR_HEIGHT_1X)

    class Entry:
        def __init__(self, x: int = -1, message: str = '', size: int = 1, align: str = 'left'):
            self.x = x
            self.message = message
            self.size = size
            self.align = align

        def __repr__(self):
            return '(x: {}, message: "{}", size: {}, align: "{}")'.format(self.x, self.message, self.size, self.align)

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

        self.entries = [MP_OLED_SSD1306_128x64.Entry() for _ in range(MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT)]

    def _show(self):
        image = Image.new('1', (self.disp.width, self.disp.height))
        draw = ImageDraw.Draw(image)
        currentY = 0
        for entry in self.entries:
            if entry.message != '':
                font = MP_OLED_SSD1306_128x64.FONT_1X    # 1X
                if entry.size == 2:
                    font = MP_OLED_SSD1306_128x64.FONT_2X
                elif entry.size == 3:
                    font = MP_OLED_SSD1306_128x64.FONT_3X
                draw.text((entry.x, currentY), entry.message, fill=1, font=font)
            currentY += MP_OLED_SSD1306_128x64.ROW_HEIGHT
        self.disp.image(image)
        self.disp.display()

    def showTextAtRow(self, row, text, size, align, color):
        row_index = int(row - 1)
        if row_index >= 0 and row_index < MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT:
            sizeInt = { '1x': 1, '2x': 2, '3x': 3 }[size]
            self.entries[row_index].message = str(text)
            self.entries[row_index].size = sizeInt
            if align == 'Left':
                self.entries[row_index].x = 0
            elif align == 'Center':
                self.entries[row_index].x = (MP_OLED_SSD1306_128x64.SCREEN_WIDTH - (MP_OLED_SSD1306_128x64.CHAR_WIDTH_1X * sizeInt * len(self.entries[row_index].message))) // 2
            elif align == 'Right':
                self.entries[row_index].x = (MP_OLED_SSD1306_128x64.SCREEN_WIDTH - (MP_OLED_SSD1306_128x64.CHAR_WIDTH_1X * sizeInt * len(self.entries[row_index].message)))
            self._show()

    def clearRow(self, row):
        rowIndex = int(row-1)
        self.entries[rowIndex].message = ''
        self.entries[rowIndex].x = 0
        self.entries[rowIndex].size = 1
        self._show()

    def clearScreen(self):
        self.entries = [MP_OLED_SSD1306_128x64.Entry() for _ in range(MP_OLED_SSD1306_128x64.MAX_ENTRY_COUNT)]
        self._show()

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "Data on screen: {0}".format(self.entries)
    
    def _dispose(self):
        self.clearScreen()