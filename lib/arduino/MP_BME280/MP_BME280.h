#ifndef MP_BME280_H
#define MP_BME280_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

class MP_BME280
{
public:
	MP_BME280();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPressure();
	double getAltitude();
	double getHumidity();
	double getTemperature();

private:
	Adafruit_BME280 bme;
	unsigned long end_time;
	double pressure;
	double altitude;
	double humidity;
	double temperature;
};

#endif
