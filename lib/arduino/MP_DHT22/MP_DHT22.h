#ifndef MP_DHT22_H
#define MP_DHT22_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "DHT_U.h"

class MP_DHT22
{
public:
	MP_DHT22(uint8_t pin);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();
	double getHumidity();

private:
	DHT sensor;
	uint8_t pin;
	
	double humidity;
	double celcius;
};

#endif
