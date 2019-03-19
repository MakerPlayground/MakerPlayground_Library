#ifndef MP_LSM6DS3_H
#define MP_LSM6DS3_H

#include "MP_DEVICE.h"

#include "SparkFunLSM6DS3.h"
#include "Wire.h"

class MP_LSM6DS3
{
public:
	MP_LSM6DS3();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getAccel_X();
	double getAccel_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

	double getGyro_X();
	double getGyro_Y();
	double getGyro_Z();

private:
	LSM6DS3 imu;
	double accel_x;
	double accel_y;
	double accel_z;
	double accel_mag;
	double gyro_x;
	double gyro_y;
	double gyro_z;	
	unsigned long end_time;
};

#endif
