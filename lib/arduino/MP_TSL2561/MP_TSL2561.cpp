#include "MP_TSL2561.h"

#define UPDATE_INTERVAL 100

MP_TSL2561::MP_TSL2561()
	: lux(0)
    , last_update(0)
{
}

int MP_TSL2561::init()
{
	Wire.begin();
	TSL2561.init(); 
	return MP_ERR_OK;
}

void MP_TSL2561::update(unsigned long current_time)
{
	if (current_time - last_update > UPDATE_INTERVAL) 
	{
		lux = TSL2561.readVisibleLux();
		last_update = current_time;
	}
}

void MP_TSL2561::printStatus()
{
    Serial.print(F("LUX = "));
	Serial.println(lux);
}

double MP_TSL2561::getIntensity()
{
	return lux;
}
