#ifndef MP_LIS3DH_H
#define MP_LIS3DH_H

#include "MP_DEVICE.h"

#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "Wire.h"

class MP_LIS3DH
{
public:
	MP_LIS3DH();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

private:
	Adafruit_LIS3DH lis;
	double accel_x;
	double accel_y;
	double accel_z;
	double accel_mag;
	unsigned long end_time;
};

#endif
