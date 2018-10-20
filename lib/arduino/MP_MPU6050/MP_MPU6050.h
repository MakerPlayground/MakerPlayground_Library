#ifndef MP_MPU6050
#define MP_MPU6050

#include "MP_DEVICE.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <MPU6050.h>

class MP_MPU6050
{
public:
	MP_MPU6050(const String &tag);

	void init();

	double getAccel_X();
	double getAcces_Y();
	double getAccel_Z();
	double getAccel_Magnitude();

	double getGyro_X();
	double getGyro_Y();
	double getGyro_Z();

	//bool checkDirection(char opt[]); //not implemented

private:
	MPU6050 accelgyro;
	const String tag;
};
#endif
