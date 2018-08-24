#include "MP_DHT11.h"

MP_DHT11::MP_DHT11(int pin, const String &tag)
	:sensor(DHT(pin,11))
	,pin(pin)
	,tag(tag)
{
}

void MP_DHT11::init()
{
	sensor.begin();
}

double MP_DHT11::getHumidity()
{
	return sensor.readTemperature();
}

double MP_DHT11::getTemperature()
{
	return sensor.readHumidity();
}
