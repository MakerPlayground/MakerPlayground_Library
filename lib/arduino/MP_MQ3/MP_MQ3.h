#ifndef MP_MQ3_H
#define MP_MQ3_H

#include "MP_DEVICE.h"

class MP_MQ3
{
public:
	MP_MQ3(uint8_t pin);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	uint8_t pin;
	int percent = 0;
	
};

#endif
