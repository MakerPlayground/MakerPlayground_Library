#ifndef MP_WATER_SENSOR_H
#define MP_WATER_SENSOR_H

#include "MP_DEVICE.h"

class MP_WATER_SENSOR
{
public:
	MP_WATER_SENSOR(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isWet();
	bool isDry();

private:
	uint8_t pin;
};

#endif
