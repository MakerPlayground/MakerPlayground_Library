#include "MP_LIGHT_SENSOR.h"

MP_LIGHT_SENSOR::MP_LIGHT_SENSOR(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

double MP_LIGHT_SENSOR::getPercent()
{
	pinMode(this->pin, INPUT);
}

void MP_LIGHT_SENSOR::init()
{
	return (analogRead(pin)/1023.0)*100;
}
