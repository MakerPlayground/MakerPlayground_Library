#ifndef MP_LSM303_Accel_I2C1_H
#define MP_LSM303_Accel_I2C1_H

#include "MP_DEVICE.h"

#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include "Wire.h"

class MP_LSM303_Accel_I2C1
{
public:
	MP_LSM303_Accel_I2C1();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

private:
	Adafruit_LSM303_Accel_Unified accel;
	double accel_x;
	double accel_y;
	double accel_z;
	double accel_mag;
	unsigned long end_time;
};

#endif
