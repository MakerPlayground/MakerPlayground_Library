#ifndef MP_SOIL_MOISTURE_H
#define MP_SOIL_MOISTURE_H

#include "MP_DEVICE.h"

class MP_SOIL_MOISTURE
{
public:
	MP_SOIL_MOISTURE(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getPercent();

private:
	uint8_t pin;
	double value;
};

#endif
