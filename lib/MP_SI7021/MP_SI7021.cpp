#include "MP_SI7021.h"

MP_SI7021::MP_SI7021(const String &tag)
	:tag(tag)
{
}

void MP_SI7021::init()
{
	sensor = Adafruit_Si7021();

	if (!sensor.begin()) {
		// Serial.println("Could not find a valid Si7021 sensor, check wiring!");
		while (1);
	}
}

double MP_SI7021::getTemperature()
{
	return sensor.readTemperature();
}

double MP_SI7021::getHumidity()
{
	return sensor.readHumidity();
}
