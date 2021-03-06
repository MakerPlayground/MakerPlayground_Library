#ifndef MP_SCT013_30A_H
#define MP_SCT013_30A_H

#include "MP_DEVICE.h"

class MP_SCT013_30A
{
public:
	MP_SCT013_30A(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAmpere();

private:
	uint8_t pin;
	double value;
	int maxValue;
	unsigned long lastReadingTime;
	unsigned long nextResetTime;
};

#endif
