#include "MP_IKB_1.h"

MP_IKB_1::MP_IKB_1()
{
}

int MP_IKB_1::init()
{
    Wire.begin();
    Wire.beginTransmission(IKB1_I2C_ADDR);
    byte error = Wire.endTransmission();
    if (error == 0)
    {
        // Reset the iKB-1
        Wire.beginTransmission(IKB1_I2C_ADDR);
        Wire.write(0);
        Wire.endTransmission();
        return ERR_OK;
    }
    return ERR_CONNECT_DEVICE;
}

void MP_IKB_1::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;
        for(uint8_t i=0; i<8; i++) {
            if (modes[i] == IKB1_MODE_INPUT)
            {
                values[i] = getA_Percent(i);
            }
        }
    }
}

void MP_IKB_1::printStatus()
{
}

void MP_IKB_1::digitalOut(uint8_t pin, uint8_t logic) 
{
    modes[pin] = IKB1_MODE_OUTPUT;
    Wire.beginTransmission(IKB1_I2C_ADDR);
    Wire.write((byte) (0x08 | pin));
    if (logic == 0) {
        Wire.write((byte) 0);
    }
    else {
        Wire.write((byte) 1);
    }
    Wire.endTransmission();
}

bool MP_IKB_1::isHigh(uint8_t pin)
{
    return getValue(pin) >= 50;
}

bool MP_IKB_1::isLow(uint8_t pin)
{
    return getValue(pin) < 50;
}

double MP_IKB_1::getA_Percent(uint8_t pin)
{
    Wire.beginTransmission(IKB1_I2C_ADDR);
    Wire.write((byte) (0x08 | pin));
    Wire.write((byte) 5);
    Wire.endTransmission();
    Wire.requestFrom(IKB1_I2C_ADDR, 1);
    while(Wire.available() < 1 && millis() <= nextReading);
    if (Wire.available())
    {
        byte value = Wire.read();
        return value;
    }
    return values[pin];
}

double MP_IKB_1::getValue(uint8_t pin)
{
    if (modes[pin] != IKB1_MODE_INPUT)
    {
        modes[pin] = IKB1_MODE_INPUT;
        values[pin] = getA_Percent(pin);
    }
    return values[pin];
}

double MP_IKB_1::getA0_Percent()
{
    return getValue(0);
}

double MP_IKB_1::getA1_Percent()
{
    return getValue(1);
}

double MP_IKB_1::getA2_Percent()
{
    return getValue(2);
}

double MP_IKB_1::getA3_Percent()
{
    return getValue(3);
}

double MP_IKB_1::getA4_Percent()
{
    return getValue(4);
}

double MP_IKB_1::getA5_Percent()
{
    return getValue(5);
}

double MP_IKB_1::getA6_Percent()
{
    return getValue(6);
}

double MP_IKB_1::getA7_Percent()
{
    return getValue(7);
}