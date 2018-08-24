#include "MP_WATER_SENSOR.h"

MP_WATER_SENSOR::MP_WATER_SENSOR(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_WATER_SENSOR::init()
{
}

bool MP_WATER_SENSOR::isWet()
{
	return analogRead(pin) > 512;
}

bool MP_WATER_SENSOR::isDry()
{
	return analogRead(pin) < 512;
}
