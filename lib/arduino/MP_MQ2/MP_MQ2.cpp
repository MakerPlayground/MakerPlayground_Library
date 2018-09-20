#include "MP_MQ2.h"

MP_MQ2::MP_MQ2(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_MQ2::init()
{
	pinMode(this->pin, INPUT);
}

double MP_MQ2::getPercent()
{
	return (analogRead(pin)/1023.0)*100;
}
