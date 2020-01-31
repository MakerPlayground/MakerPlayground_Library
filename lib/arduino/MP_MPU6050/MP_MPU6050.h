#ifndef MP_MPU6050_H
#define MP_MPU6050_H

#include "MP_DEVICE.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include <Wire.h>
#endif

class MP_MPU6050
{
public:
	MP_MPU6050(bool ad0high);
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
	double accel_x, accel_y, accel_z, accel_mag;
	double gyro_x, gyro_y, gyro_z;
	MPU6050 accelgyro;

	int16_t ax, ay, az, gx, gy, gz;
	unsigned long next_update_time = 0;
};

#endif
