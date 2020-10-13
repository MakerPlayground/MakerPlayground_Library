#ifndef MP_IMU_M5Atom_H
#define MP_IMU_M5Atom_H

#include <MP_DEVICE.h>
#include <M5Atom.h>

class MP_IMU_M5Atom
{
public:
	MP_IMU_M5Atom();
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
	float accel_x, accel_y, accel_z, accel_mag;
	float gyro_x, gyro_y, gyro_z;
	unsigned long next_update_time = 0;
};

#endif
