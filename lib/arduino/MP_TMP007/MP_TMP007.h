#ifndef MP_TMP007_H
#define MP_TMP007_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Adafruit_TMP007.h"

class MP_TMP007
{
public:
	MP_TMP007();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();

private:
	Adafruit_TMP007 tmp007;
	double celcius;
	unsigned long end_time;
};

#endif
