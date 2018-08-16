#include "MP_BUTTON.h"

MP_BUTTON::MP_BUTTON(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_BUTTON::init()
{
	pinMode(pin, INPUT_PULLUP);
}

boolean MP_BUTTON::isReleased()
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

boolean MP_BUTTON::isPressed()
{
	if(digitalRead(pin)==LOW)
	{
		delay(300);
		return true;
	}
	return false;
}