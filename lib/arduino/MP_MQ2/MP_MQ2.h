#ifndef MP_MQ2_H
#define MP_MQ2_H

#include "MP_DEVICE.h"

class MP_MQ2
{
public:
	MP_MQ2(uint8_t pin);

	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getPercent();

private:
	uint8_t pin;
	int percent = 0;
};

#endif
