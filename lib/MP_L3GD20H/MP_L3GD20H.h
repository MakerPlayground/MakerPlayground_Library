#ifndef MP_L3GD20H_H
#define MP_L3GD20H_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_L3GD20_U.h"

class MP_L3GD20H
{
public:
	MP_L3GD20H(const String &tag);

	void init();
	double getGyro_X();
	double getGyro_Y();
	double getGyro_Z();

private:
	Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
	sensors_event_t event;
	const String tag;
};

#endif
