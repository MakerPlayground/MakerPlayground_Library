#include "MP_TRIMPOT.h"

MP_TRIMPOT::MP_TRIMPOT(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_TRIMPOT::init()
{
	pinMode(this->pin, INPUT);
}

double MP_TRIMPOT::getPercent()
{
	return (analogRead(pin)/1023.0)*100;
}
