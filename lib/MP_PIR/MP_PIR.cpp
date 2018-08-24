#include "MP_PIR.h"

MP_PIR::MP_PIR(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_PIR::init()
{
	pinMode(this->pin, INPUT);
}

int MP_PIR::isDetected()
{
	return digitalRead(pin) == HIGH;
}

int MP_PIR::isNotDetected()
{
	return digitalRead(pin) == LOW;
}
