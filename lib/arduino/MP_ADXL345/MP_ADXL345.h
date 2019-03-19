#ifndef MP_ADXL345_H
#define MP_ADXL345_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_ADXL345_U.h"

class MP_ADXL345
{
public:
	MP_ADXL345();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

private:
	Adafruit_ADXL345_Unified accel;
	sensors_event_t event;
	unsigned long old_time;
};
#endif
