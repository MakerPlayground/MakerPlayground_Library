#ifndef MP_TRIMPOT_H
#define MP_TRIMPOT_H

#include <Arduino.h>

class MP_TRIMPOT
{
public:
	MP_TRIMPOT(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getPercent();

private:
	uint8_t pin;
	double value;
};

#endif
