#ifndef MP_DHT11_H
#define MP_DHT11_H

#include "MP_DEVICE.h"
#include "DHT_U.h"

class MP_DHT11
{
public:
	MP_DHT11(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getHumidity();
	double getTemperature();

private:
	DHT sensor;
	uint8_t pin;
	
	double humidity;
	double celcius;
};

#endif
