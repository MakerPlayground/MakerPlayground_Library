#ifndef MP_PIR_H
#define MP_PIR_H

#include <Arduino.h>

class MP_PIR
{
public:
	MP_PIR(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	int isDetected();
	int isNotDetected();

private:
	uint8_t pin;
	int isMotionDetected;
};
#endif