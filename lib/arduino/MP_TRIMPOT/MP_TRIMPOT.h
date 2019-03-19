#ifndef MP_TRIMPOT_H
#define MP_TRIMPOT_H

#include "MP_DEVICE.h"

class MP_TRIMPOT
{
public:
	MP_TRIMPOT(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	uint8_t pin;
	double value;
};

#endif
