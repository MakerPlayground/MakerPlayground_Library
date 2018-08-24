#ifndef MP_DHT11_H
#define MP_DHT11_H

#include <Arduino.h>
#include "DHT.h"

class MP_DHT11
{
public:
	MP_DHT11(int pin, const String &tag);
	void init();
	double getHumidity();
	double getTemperature();

private:
	DHT sensor;
	uint8_t pin;
	const String tag;

};

#endif
