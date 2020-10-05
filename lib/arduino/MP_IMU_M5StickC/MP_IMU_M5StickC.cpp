#include "MP_IMU_M5StickC.h"

#define GRAVITY 9.81

MP_IMU_M5StickC::MP_IMU_M5StickC()
	: accel_x(0.0)
	, accel_y(0.0)
	, accel_z(0.0)
	, accel_mag(0.0)
	, gyro_x(0.0)
	, gyro_y(0.0)
	, gyro_z(0.0)
{
}

int MP_IMU_M5StickC::init()
{
    M5.begin();
    M5.IMU.Init();
	return MP_ERR_OK;
}

void MP_IMU_M5StickC::update(unsigned long current_time)
{
	if (next_update_time <= current_time)
	{
		M5.IMU.getAccelData(&accel_x, &accel_y, &accel_z);
		accel_x = accel_x * GRAVITY;
		accel_y = accel_y * GRAVITY;
		accel_z = accel_z * GRAVITY;
		accel_mag = sqrt(accel_x*accel_x + accel_y*accel_y + accel_z*accel_z);
		M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
		next_update_time = current_time + 100;
	}
}

void MP_IMU_M5StickC::printStatus()
{
	Serial.print(F("accel (x, y, z, mag) = ("));
	Serial.print(accel_x);
	Serial.print(F(","));
	Serial.print(accel_y);
	Serial.print(F(","));
	Serial.print(accel_z);
	Serial.print(F(","));
	Serial.print(accel_mag);
	Serial.println(F(")"));
	
	Serial.print(F("gyro (x, y, z) = ("));
	Serial.print(gyro_x);
	Serial.print(F(","));
	Serial.print(gyro_y);
	Serial.print(F(","));
	Serial.print(gyro_z);
	Serial.println(F(")"));
}

double MP_IMU_M5StickC::getAccel_X()
{
	return accel_x;
}

double MP_IMU_M5StickC::getAccel_Y()
{
	return accel_y;
}

double MP_IMU_M5StickC::getAccel_Z()
{
	return accel_z;
}

double MP_IMU_M5StickC::getAccel_Magnitude()
{
	return accel_mag;
}

double MP_IMU_M5StickC::getGyro_X()
{
    return gyro_x;
}

double MP_IMU_M5StickC::getGyro_Y()
{	
    return gyro_y;
}

double MP_IMU_M5StickC::getGyro_Z()
{
    return gyro_z;
}
