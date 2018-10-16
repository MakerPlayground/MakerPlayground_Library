#ifndef MP_SCT013_30A_H
#define MP_SCT013_30A_H

#include <Arduino.h>
class MP_SCT013_30A
{
public:
	MP_SCT013_30A(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getAmpere();

private:
	uint8_t pin;
	double value;
	int maxValue;
	unsigned long lastReadingTime;
	unsigned long nextResetTime;
};

#endif
