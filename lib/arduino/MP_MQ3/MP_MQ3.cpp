#include "MP_MQ3.h"

MP_MQ3::MP_MQ3(uint8_t pin, const Sting &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_MQ3::init()
{
	pinMode(this->pin, INPUT);
}

double MP_MQ3::getPercent()
{
	return (analogRead(pin)/1023.0)*100;
}
