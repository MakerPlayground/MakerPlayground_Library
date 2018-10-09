#ifndef MP_BMP280_H
#define MP_BMP280_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

class MP_BMP280
{
public:
	MP_BMP280();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getPressure();
	double getAltitude();
	double getTemperature();

private:
	Adafruit_BMP280 bmp;
	unsigned long end_time;
	double pressure;
	double altitude;
	double temperature;
};

#endif
