#ifndef MP_BME280_H
#define MP_BME280_H

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

class MP_BME280
{
public:
	MP_BME280(const String &tag);

	void init();
	double getPressure();
	double getAltitude();
	double getHumidity();
	double getTemperature();

private:
	Adafruit_BME280 bme;
	const String tag;
};

#endif
