#ifndef MP_MICROPHONE_H
#define MP_MICROPHONE_H

#include <Arduino.h>

class MP_MICROPHONE
{
public:
	MP_MICROPHONE(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getSoundLevel();

private:
	uint8_t pin;
	double soundLevel;
};

#endif
