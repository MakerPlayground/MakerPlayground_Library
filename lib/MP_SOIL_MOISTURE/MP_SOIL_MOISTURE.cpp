#include "MP_SOIL_MOISTURE.h"

MP_SOIL_MOISTURE::MP_SOIL_MOISTURE(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

int MP_SOIL_MOISTURE::init()
{
	pinMode(data, INPUT);
	pinMode(en, OUTPUT);
	return 0;
}

double MP_SOIL_MOISTURE::getHumidity()
{
	return (analogRead(pin) / 1023.0) * 100.0;
}
