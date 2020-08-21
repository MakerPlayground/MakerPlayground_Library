#ifndef MP_LIS2MDL_I2C1_H
#define MP_LIS2MDL_I2C1_H

#include "MP_DEVICE.h"

#include <Adafruit_LIS2MDL.h>
#include <Adafruit_Sensor.h>
#include "Wire.h"

class MP_LIS2MDL_I2C1
{
public:
	MP_LIS2MDL_I2C1();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getMag_X();
	double getMag_Y();
	double getMag_Z();
	double getHeading();
	bool checkDirection(uint8_t direction);

private:
	Adafruit_LIS2MDL lis2mdl;
	double mag_x;
	double mag_y;
	double mag_z;
	double heading;
	unsigned long end_time;
};

#endif
