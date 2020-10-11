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
	LSM6DS3 imu = LSM6DS3(I2C_MODE, 0x6A);
	double accel_x = 0.0;
	double accel_y = 0.0;
	double accel_z = 0.0;
	double accel_mag = 0.0;
	double gyro_x = 0.0;
	double gyro_y = 0.0;
	double gyro_z = 0.0;
	unsigned long end_time;
};

#endif
