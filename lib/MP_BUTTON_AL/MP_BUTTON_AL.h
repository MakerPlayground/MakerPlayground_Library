#ifndef MP_BUTTON_AL_H
#define MP_BUTTON_AL_H

#include <Arduino.h>

class MP_BUTTON_AL
{
public:
	MP_BUTTON_AL(uint8_t pin, const String &tag);

	void init();
	boolean isReleased();
	boolean isPressed();

private:
	uint8_t pin;
	const String tag;
};

#endif
