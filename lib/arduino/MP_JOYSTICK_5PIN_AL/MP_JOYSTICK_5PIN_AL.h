#ifndef MP_JOYSTICK_5PIN_AL_H
#define MP_JOYSTICK_5PIN_AL_H

#include "MP_DEVICE.h"

class MP_JOYSTICK_5PIN_AL
{
public:
	MP_JOYSTICK_5PIN_AL(uint8_t upPin, uint8_t leftPin, uint8_t rightPin, uint8_t pressPin, uint8_t downPin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isUpPress();
	bool isDownPress();
	bool isLeftPress();
	bool isRightPress();
	bool isMiddlePress();
	bool isUpRelease();
	bool isDownRelease();
	bool isLeftRelease();
	bool isRightRelease();
	bool isMiddleRelease();
	bool isAllRelease();

private:
	uint8_t upPin;
	uint8_t leftPin;
	uint8_t rightPin;
	uint8_t pressPin;
	uint8_t downPin;
};

#endif
