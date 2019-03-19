#ifndef MP_L3GD20H_H
#define MP_L3GD20H_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_L3GD20_U.h"

class MP_L3GD20H
{
public:
	MP_L3GD20H();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getGyro_X();
	double getGyro_Y();
	double getGyro_Z();

private:
	Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
	sensors_event_t event;
	unsigned long end_time;
};

#endif
