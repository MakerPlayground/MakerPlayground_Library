#ifndef MP_MPU9250_H
#define MP_MPU9250_H

#include "MP_DEVICE.h"
#include "Wire.h"
#include "FS.h"
#include "SD.h"
#include "utility/MPU9250.h"

class MP_MPU9250
{
public:
	MP_MPU9250();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getAccel_X();
	double getAcces_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

	double getGyro_X();
	double getGyro_Y();
	double getGyro_Z();

	double getMag_X();
    double getMag_Y();
    double getMag_Z();

private:
	MPU9250 imu;
	double accelMagnitude;
	unsigned long nextUpdateTime;
};

#endif
