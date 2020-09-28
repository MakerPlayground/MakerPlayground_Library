import lcd, image
import MakerPlayground as mp

class MP_TFT_SIPEED_AMIGO:
    CHAR_WIDTH_1X = 8
    CHAR_HEIGHT_1X = 10
    NUM_ROWS = 32
    COLORS = [(0, 0, 255),      # TFT_BLUE
              (0, 255, 255),    # TFT_CYAN
              (0, 128, 128),    # TFT_DARKCYAN
              (0, 128, 0),      # TFT_DARKGREEN
              (128, 128, 128),  # TFT_DARKGREY
              (0, 255, 0),      # TFT_GREEN
              (180, 255, 0),    # TFT_GREENYELLOW
              (211, 211, 211),  # TFT_LIGHTGREY
              (255, 0, 255),    # TFT_MAGENTA
              (128, 0, 0),      # TFT_MAROON
              (0, 0, 128),      # TFT_NAVY
              (128, 128, 0),    # TFT_OLIVE
              (255, 180, 0),    # TFT_ORANGE
              (255, 192, 203),  # TFT_PINK
              (128, 0, 128),    # TFT_PURPLE
              (255, 255, 255),  # TFT_WHITE
              (255, 0, 0),      # TFT_RED
              (255, 255, 0)]    # TFT_YELLOW

    def __init__(self):
        pass

    def init(self):
        lcd.init(freq=20000000)
        self.framebuffer = image.Image(size=(lcd.width(), lcd.height()))
        self.framebuffer.clear()
        self.rowHeight = [1 for i in range(MP_TFT_SIPEED_AMIGO.NUM_ROWS)]
        return mp.ERR_OK

    def update(self, currentTime):
        pass

    def printStatus(self):
        pass

    def showTextAtRow(self, row, text, size, align, color):
        row = int(row)
        if row < 1 or row > MP_TFT_SIPEED_AMIGO.NUM_ROWS:
            return

        if align == 0: # left
            x = 0
        elif align == 1: # center
            x = (lcd.width() - (MP_TFT_SIPEED_AMIGO.CHAR_WIDTH_1X * size * len(text))) / 2
        elif align == 2: # right
            x = lcd.width() - (MP_TFT_SIPEED_AMIGO.CHAR_WIDTH_1X * size * len(text))

        self.framebuffer.draw_rectangle((0, (row - 1) * MP_TFT_SIPEED_AMIGO.CHAR_HEIGHT_1X, lcd.width(), self.rowHeight[row-1] * MP_TFT_SIPEED_AMIGO.CHAR_HEIGHT_1X), fill=True, color=(0, 0, 0))

        self.rowHeight[row-1] = size
        self.framebuffer.draw_string(int(x), (row - 1) * MP_TFT_SIPEED_AMIGO.CHAR_HEIGHT_1X, text, color=MP_TFT_SIPEED_AMIGO.COLORS[color], scale=size, mono_space=True)
        lcd.display(self.framebuffer)

    def showImage(self, image):
        if image is not None:
            self.framebuffer.draw_image(image, 0, 0, lcd.width()/image.width(), lcd.height()/image.height())
            lcd.display(self.framebuffer)

    def drawRectangle(self, left, top, right, bottom, color, thickness):
        self.framebuffer.draw_rectangle((int(left * lcd.width()), int(top * lcd.height()), int((right-left) * lcd.width()), int((bottom-top) * lcd.height())), fill=False, color=MP_TFT_SIPEED_AMIGO.COLORS[color], thickness=int(thickness))
        lcd.display(self.framebuffer)

    def clearRow(self, row):
        self.framebuffer.draw_rectangle((0, (row - 1) * MP_TFT_SIPEED_AMIGO.CHAR_HEIGHT_1X, lcd.width(), self.rowHeight[row-1] * MP_TFT_SIPEED_AMIGO.CHAR_HEIGHT_1X), fill=True, color=(0, 0, 0))
        self.rowHeight[row-1] = 1
        lcd.display(self.framebuffer)

    def clearScreen(self):
        self.framebuffer.clear()
        lcd.display(self.framebuffer)