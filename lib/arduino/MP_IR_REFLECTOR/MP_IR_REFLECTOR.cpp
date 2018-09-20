#include "MP_IR_REFLECTOR.h"

MP_IR_REFLECTOR::MP_IR_REFLECTOR(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_IR_REFLECTOR::init()
{
	pinMode(this->pin, INPUT);
}

int MP_IR_REFLECTOR::isDetected()
{
	return digitalRead(pin) == LOW;
}

int MP_IR_REFLECTOR::isNotDetected()
{
	return digitalRead(pin) == HIGH;
}
