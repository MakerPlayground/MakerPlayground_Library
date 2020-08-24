#include "MP_WATER_SENSOR.h"

MP_WATER_SENSOR::MP_WATER_SENSOR(uint8_t pin)
	:pin(pin)
{
}


int MP_WATER_SENSOR::init()
{
	return MP_ERR_OK;
}

void MP_WATER_SENSOR::update(unsigned long current_time)
{
	
}

void MP_WATER_SENSOR::printStatus()
{
	Serial.print(F("current value = "));
	Serial.println(analogRead(pin));
}

bool MP_WATER_SENSOR::isWet()
{
	return analogRead(pin) > 512;
}

bool MP_WATER_SENSOR::isDry()
{
	return analogRead(pin) < 512;
}
