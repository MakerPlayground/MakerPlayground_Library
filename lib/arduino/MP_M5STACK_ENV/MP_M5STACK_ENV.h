#ifndef MP_M5STACK_ENV_H
#define MP_M5STACK_ENV_H

#include "MP_DEVICE.h"
#include "M5Stack.h"
#include <Wire.h>
#include "dht.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

class MP_M5STACK_ENV
{
public:
	MP_M5STACK_ENV();

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPressure();
	double getAltitude();
	double getHumidity();
	double getTemperature();

private:
	dht12 sensor;
	Adafruit_BMP280 bmp;
	double temperature;
	double humidity;
	double pressure;
	double altitude;
	unsigned long last_update = 0;
};

#endif
