#ifndef MP_PERCENT_REFLECTANCE_H
#define MP_PERCENT_REFLECTANCE_H

#include "MP_DEVICE.h"

class MP_PERCENT_REFLECTANCE
{
public:
	MP_PERCENT_REFLECTANCE(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getReflectance();

private:
	uint8_t pin;
	double value;
};

#endif
