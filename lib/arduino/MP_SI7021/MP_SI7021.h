#ifndef MP_SI7021_H
#define MP_SI7021_H

#include "MP_DEVICE.h"
#include "Adafruit_Si7021.h"

class MP_SI7021
{
public:
	MP_SI7021();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();
	double getHumidity();

private:
	Adafruit_Si7021 sensor;
	unsigned long end_time;
	double temperature;
	double humidity;
};

#endif
