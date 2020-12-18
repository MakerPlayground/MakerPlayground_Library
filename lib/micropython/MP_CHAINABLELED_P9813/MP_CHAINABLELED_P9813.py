import MakerPlayground as mp
import time

class MP_CHAINABLELED_P9813:
    def __init__(self, clk, data, number_leds):
        self.clk = clk
        self.data = data

        pinMode(self.clk, GPIO_DIR.OUT)
        pinMode(self.data, GPIO_DIR.OUT)

        digitalWrite(self.clk, GPIO_STATE.HIGH)
        digitalWrite(self.data, GPIO_STATE.LOW)

        self.status = []
        for i in range(number_leds):
            self.status.append([0,0,0])

    def check_RGB(self, value):
        if not value in range(0,256):
            raise ValueError("value: [0, 255]")

    def check_HSB(self, value):
        if not value in range(0.0,1.0):
            raise ValueError("value: [0, 1]")

    # red, green, blue
    def set_RGB(self, led, r, g, b):
        self.check_RGB(r)
        self.check_RGB(g)
        self.check_RGB(b)

        self.send_byte(0x00)
        self.send_byte(0x00)
        self.send_byte(0x00)
        self.send_byte(0x00)
        for i in range(len(self.status)):
            if i == led:
                self.status[i]=[r, g, b]
            self.send_color(self.status[i][0], self.status[i][1], self.status[i][2])
        self.send_byte(0x00)
        self.send_byte(0x00)
        self.send_byte(0x00)
        self.send_byte(0x00)

    # hue, saturation, brightness
    def set_HSB(self, led, h, s, b):
        self.check_HSB(h)
        self.check_HSB(s)
        self.check_HSB(b)
        if s == 0:
            r = b
            g = b
            b = b
        else:
            q = b*(1.0+s) if b<0.5 else b+s-b*s
            p = 2.0 * b -q
            r = int(self.hue_to_rgb(p, q, h + 1/3)) & 0xFF
            g = int(self.hue_to_rgb(p, q, hue)) & 0xFF
            b = int(self.hue_to_rgb(p, q, hue - 1/3)) & 0xFF

        self.set_RGB(led, r, g, b)

    def send_byte(self, data):
        for i in range(8):
            if data & 0x80:
                digitalWrite(self.data, GPIO_STATE.HIGH)
            else:
                digitalWrite(self.data, GPIO_STATE.LOW)
            self.write_clk()
            data <<= 1

    def write_clk(self):
        digitalWrite(self.clk, GPIO_STATE.LOW)
        time.sleep_us(20)
        digitalWrite(self.clk, GPIO_STATE.HIGH)
        time.sleep_us(20)

    def send_color(self, r, g, b):
        prefix = 0xC0
        if (b & 0x80) == 0:
            prefix |= 0x20
        if (b & 0x40) == 0:
            prefix |= 0x10
        if (g & 0x80) == 0:
            prefix |= 0x08
        if (g & 0x40) == 0:
            prefix |= 0x04
        if (r & 0x80) == 0:
            prefix |= 0x02
        if (r & 0x40) == 0:
            prefix |= 0x01
        self.send_byte(prefix)
        self.send_byte(b)
        self.send_byte(g)
        self.send_byte(r)

    def hue_to_rgb(self, p, q, t):
        if t < 0:
            t += 1
        if t > 1:
            t -= 1
        if t < 1/6:
            return p + (q - p) * 6.0 * t
        if t < 1/2:
            return q
        if t < 2/3:
            return p + (q - p) * (2/3 - t) * 6
        return p