#ifndef MP_SHT_H
#define MP_SHT_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "SHTSensor.h"

class MP_SHT
{
public:
	MP_SHT();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();
	double getHumidity();

private:
	SHTSensor sht;
};

#endif
