from MakerPlayground.Devices.MP_Device import MP_Device
import pigpio
import time
from MakerPlayground import MPInteractive

class MP_IKB_1(MP_Device):
    
    I2C_ADDR = 0x48
    INPUT_ONLY = 0
    OUTPUT_ONLY = 1
    BOTH = 2
    MOTOR_FORWARD = 1
    MOTOR_BACKWARD = 0

    delay = 0.005

    def __init__(self):
        self.values = [0, 0, 0, 0, 0, 0, 0, 0]
        self.pi = pigpio.pi()
        self.nextReading = 0
        self.pi.set_mode(2, pigpio.ALT0)
        self.pi.set_mode(3, pigpio.ALT0)
        time.sleep(0.5)
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        self.pi.i2c_write_byte(handle, 0x00)
        self.pi.i2c_close(handle)
        

    def update(self, currentTime):
        if currentTime >= self.nextReading:
            self.nextReading = currentTime + 0.100
            for i in range(8):
                self.values[i] = self.getA_Percent(i)
            
    def getStatus(self):
        return ""

    def digitalOut(self, pin, logic):
        time.sleep(MP_IKB_1.delay)
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        if logic == 0:
            self.pi.i2c_write_byte_data(handle, 0x08 | pin, 0)
            self.values[pin] = 0
        else:
            self.pi.i2c_write_byte_data(handle, 0x08 | pin, 1)
            self.values[pin] = 1
        self.pi.i2c_close(handle)


    def isHigh(self, pin):
        return self.getValue(pin) >= 50

    def isLow(self, pin):
        return self.getValue(pin) < 50

    def getA_Percent(self, pin):
        if not MPInteractive.is_freeze_sensor:
            handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
            time.sleep(MP_IKB_1.delay)
            self.pi.i2c_write_byte_data(handle, 0x08 | pin, 5)
            time.sleep(MP_IKB_1.delay)
            self.values[pin] = self.pi.i2c_read_byte(handle)
            self.pi.i2c_close(handle)

        return self.values[pin]


    def getValue(self, pin):
        self.values[pin] = self.getA_Percent(pin)
        return self.values[pin]


    def getA0_Percent(self):
        return self.getValue(0)


    def getA1_Percent(self):
        return self.getValue(1)


    def getA2_Percent(self):
        return self.getValue(2)


    def getA3_Percent(self):
        return self.getValue(3)


    def getA4_Percent(self):
        return self.getValue(4)


    def getA5_Percent(self):
        return self.getValue(5)


    def getA6_Percent(self):
        return self.getValue(6)


    def getA7_Percent(self):
        return self.getValue(7)


    def moveServo(self, channel, degree):
        if channel < 1 or channel > 6: 
            return
        channel = int(channel)
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        time.sleep(MP_IKB_1.delay)
        self.pi.i2c_write_byte_data(handle, 0x40 | (1 << (channel-1)), int(degree))
        self.pi.i2c_close(handle)


    def freeServo(self, channel):
        if channel < 1 or channel > 6:
            return
        channel = int(channel)
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        time.sleep(MP_IKB_1.delay)
        self.pi.i2c_write_byte_data(handle, 0x40 | (1 << (channel-1)), 255)
        self.pi.i2c_close(handle)


    def motorOn(self, channel, direction, percent):
        if channel < 1 or channel > 4:
            return
        channel = int(channel)
        speed = int(percent)
        if direction == MP_IKB_1.MOTOR_BACKWARD:
            speed = 256 - speed
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        time.sleep(MP_IKB_1.delay)
        self.pi.i2c_write_byte_data(handle, 0x20 | (1 << (channel-1)), speed)
        self.pi.i2c_close(handle)


    def motorOff(self, channel):
        if channel < 1 or channel > 4:
            return
        channel = int(channel)
        handle = self.pi.i2c_open(1, MP_IKB_1.I2C_ADDR)
        time.sleep(MP_IKB_1.delay)
        self.pi.i2c_write_byte_data(handle, 0x20 | (1 << (channel-1)), 0)
        self.pi.i2c_close(handle)


    def _dispose(self):
        # self.pi.i2c_close(handle)
        self.pi.stop()