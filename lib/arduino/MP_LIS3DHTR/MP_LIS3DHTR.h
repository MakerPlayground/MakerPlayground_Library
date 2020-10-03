#ifndef MP_LIS3DHTR_H
#define MP_LIS3DHTR_H

#include "MP_DEVICE.h"

#include "LIS3DHTR.h"
#include <Wire.h>

class MP_LIS3DHTR
{
public:
	MP_LIS3DHTR();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

private:
	LIS3DHTR<TwoWire> lis;
	double accel_x;
	double accel_y;
	double accel_z;
	double accel_mag;
	unsigned long end_time;
};

#endif
