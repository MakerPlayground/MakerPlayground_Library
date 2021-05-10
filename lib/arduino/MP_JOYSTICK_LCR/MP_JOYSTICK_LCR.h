#ifndef MP_JOYSTICK_LCR_H
#define MP_JOYSTICK_LCR_H

#include "MP_DEVICE.h"

class MP_JOYSTICK_LCR
{
public:
	MP_JOYSTICK_LCR(uint8_t leftPin, uint8_t middlePin, uint8_t rightPin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isLeftPress();
	bool isRightPress();
	bool isMiddlePress();
	bool isLeftRelease();
	bool isRightRelease();
	bool isMiddleRelease();
	bool isAllRelease();

private:
	uint8_t leftPin;
	uint8_t middlePin;
	uint8_t rightPin;
};

#endif
