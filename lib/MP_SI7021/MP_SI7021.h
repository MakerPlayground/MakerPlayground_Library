#ifndef MP_SI7021_H
#define MP_SI7021_H

#include <Arduino.h>
#include "Adafruit_Si7021.h"

class MP_SI7021
{
public:
	MP_SI7021(const String &tag);

	void init();
	double getTemperature();
	double getHumidity();

private:
	Adafruit_Si7021 sensor;
	const String tag;
};

#endif
