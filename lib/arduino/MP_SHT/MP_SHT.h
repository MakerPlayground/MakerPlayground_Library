#ifndef MP_SHT_H
#define MP_SHT_H

#include <Arduino.h>
#include <Wire.h>
#include "SHTSensor.h"

class MP_SHT
{
public:
	MP_SHT();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getTemperature();
	double getHumidity();

private:
	SHTSensor sht;
};

#endif
