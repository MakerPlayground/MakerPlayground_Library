#include "MP_LM73_I2C1_ESP32.h"

#define LM73_ADDR 0x4D

MP_LM73_I2C1_ESP32::MP_LM73_I2C1_ESP32()
{
}

int MP_LM73_I2C1_ESP32::init()
{
	Wire1.begin(4, 5);
	return ERR_OK;
}

void MP_LM73_I2C1_ESP32::update(unsigned long current_time) 
{
	if (current_time - end_time > 10) {
		Wire1.beginTransmission(LM73_ADDR);
        Wire1.write(0x00); // Temperature Data Register
        Wire1.endTransmission();
        
        uint8_t count = Wire1.requestFrom(LM73_ADDR, 2);
        double temp = 0.0;
        if (count == 2) {
            byte buff[2];
            buff[0] = Wire1.read();
            buff[1] = Wire1.read();
            temp += (int)(buff[0]<<1);
            if (buff[1]&0b10000000) temp += 1.0;
            if (buff[1]&0b01000000) temp += 0.5;
            if (buff[1]&0b00100000) temp += 0.25;
            if (buff[0]&0b10000000) temp *= -1.0;
        }
        temperature = temp;
		end_time = current_time;
	}
}

void MP_LM73_I2C1_ESP32::printStatus()
{
	Serial.print(F("temp = "));
	Serial.print(this->temperature);
}

double MP_LM73_I2C1_ESP32::getTemperature()
{
	return this->temperature;
}