#ifndef MP_ADXL345_H
#define MP_ADXL345_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345_U.h"

class MP_ADXL345
{
public:
	MP_ADXL345();

	void init();
	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

private:
	Adafruit_ADXL345_Unified accel;
};
#endif
