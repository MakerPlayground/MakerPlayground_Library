#include "MP_BUTTON_AL.h"

MP_BUTTON_AL::MP_BUTTON_AL(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_BUTTON_AL::init()
{
	pinMode(pin, INPUT_PULLUP);
}

boolean MP_BUTTON_AL::isReleased()
{
	if(digitalRead(pin)==LOW)
	{
		delay(30);
		while(digitalRead(pin)==LOW);
		delay(30);
		return true;
	}
	return false;
}

boolean MP_BUTTON_AL::isPressed()
{
	if(digitalRead(pin)==LOW)
	{
		delay(300);
		return true;
	}
	return false;
}