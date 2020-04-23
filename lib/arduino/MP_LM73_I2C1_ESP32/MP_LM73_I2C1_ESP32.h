#ifndef MP_LM73_I2C1_ESP32_H
#define MP_LM73_I2C1_ESP32_H

#include "MP_DEVICE.h"
#include "Wire.h"

class MP_LM73_I2C1_ESP32
{
public:
	MP_LM73_I2C1_ESP32();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();

private:
	double temperature;
	unsigned long end_time = 0;
};

#endif
