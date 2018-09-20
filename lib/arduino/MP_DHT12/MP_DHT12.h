#ifndef MP_DHT12_H
#define MP_DHT12_H

#include <Arduino.h>
#include <Wire.h>
#include "dht_dplasa.h"

class MP_DHT12
{
public:
	MP_DHT12(const String &tag);

	void init();
	double getTemperature();
	double getHumidity();

private:
	dht12 sensor;
	const String tag;
}

#endif
