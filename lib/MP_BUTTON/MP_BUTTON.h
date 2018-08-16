#ifndef MP_BUTTON_H
#define MP_BUTTON_H

#include <Arduino.h>

class MP_BUTTON
{
public:
	MP_BUTTON(uint8_t pin, const String &tag);

	void init();
	boolean isReleased();
	boolean isPressed();

private:
	uint8_t pin;
	const String tag;
};

#endif
