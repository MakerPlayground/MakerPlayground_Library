from machine import I2C
axp173 = I2C(I2C.I2C0, freq=100000, scl=24, sda=27)
axp173.writeto_mem(0x34, 0x27, 0x20)
axp173.writeto_mem(0x34, 0x28, 0x0C)
axp173.writeto_mem(0x34, 0x36, 0xCC, mem_size=8)