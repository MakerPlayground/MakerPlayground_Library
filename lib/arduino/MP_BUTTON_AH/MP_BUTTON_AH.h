#ifndef MP_BUTTON_AH_H
#define MP_BUTTON_AH_H

#include "MP_DEVICE.h"

class MP_BUTTON_AH
{
public:
	MP_BUTTON_AH(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	bool isPress();
	bool isPressAndRelease();
	bool isNotPress();

private:
	uint8_t pin;
	unsigned long checkpoint;
	enum ButtonState { NOTHING, PRESSED, JUST_RELEASE };
	ButtonState state = NOTHING;
};

#endif
