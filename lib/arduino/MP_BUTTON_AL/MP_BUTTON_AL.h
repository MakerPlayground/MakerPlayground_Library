#ifndef MP_BUTTON_AL_H
#define MP_BUTTON_AL_H

#include "MP_DEVICE.h"

class MP_BUTTON_AL
{
public:
	MP_BUTTON_AL(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	bool isPress();
	bool isPressAndRelease();
	bool isNotPress();

private:
	uint8_t pin;
};

#endif
