#ifndef MP_GROVE_ULTRASONIC_RANGER_H
#define MP_GROVE_ULTRASONIC_RANGER_H

#include "MP_DEVICE.h"

class MP_GROVE_ULTRASONIC_RANGER
{
public:
	MP_GROVE_ULTRASONIC_RANGER(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getDistance();

private:
	uint8_t pin;
	double cm;
};

#endif
