#ifndef MP_DHT12_H
#define MP_DHT12_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "dht.h"

class MP_DHT12
{
public:
	MP_DHT12();

	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getTemperature();
	double getHumidity();

private:
	dht12 sensor;
	double temperature;
	double humidity;
	unsigned long last_update = 0;
};

#endif
