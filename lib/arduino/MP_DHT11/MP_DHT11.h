#ifndef MP_DHT11_H
#define MP_DHT11_H

#include <Arduino.h>
#include "DHT.h"

class MP_DHT11
{
public:
	MP_DHT11(int pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getHumidity();
	double getTemperature();

private:
	DHT sensor;
	uint8_t pin;
	
	double humidity;
	double celcius;
};

#endif
