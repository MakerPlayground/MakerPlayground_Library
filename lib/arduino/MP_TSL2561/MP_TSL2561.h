#ifndef MP_TSL2561_H
#define MP_TSL2561_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Digital_Light_TSL2561.h"

class MP_TSL2561
{
public:
	MP_TSL2561();

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getIntensity();

private:
	double lux;
	unsigned long last_update;
};

#endif
