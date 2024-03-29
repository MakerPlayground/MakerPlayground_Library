#include "MP_LSM6DS3.h"

#define GRAVITY 9.80665

MP_LSM6DS3::MP_LSM6DS3()
{
}

int MP_LSM6DS3::init()
{
	end_time = 0;
	if(imu.begin() != IMU_SUCCESS) {
		return MP_ERR_CONNECT_DEVICE;
	}
	return MP_ERR_OK;
}

void MP_LSM6DS3::update(unsigned long current_time) 
{
	if (current_time - end_time > 10) {
		this->accel_x = imu.readFloatAccelX() * GRAVITY;
		this->accel_y = imu.readFloatAccelY() * GRAVITY;
		this->accel_z = imu.readFloatAccelZ() * GRAVITY;
		this->accel_mag = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
		this->gyro_x = imu.readFloatGyroX();
		this->gyro_y = imu.readFloatGyroY();
		this->gyro_z = imu.readFloatGyroZ();
		end_time = current_time;
	}
}

void MP_LSM6DS3::printStatus()
{
	Serial.print(F("ax,ay,az,amag = "));
	Serial.print(this->accel_x);
	Serial.print(F(","));
	Serial.print(this->accel_y);
	Serial.print(F(","));
	Serial.print(this->accel_z);
	Serial.print(F(","));
	Serial.print(this->accel_mag);
	
	Serial.print(F(" | gx,gy,gz = "));
	Serial.print(this->gyro_x);
	Serial.print(F(","));
	Serial.print(this->gyro_y);
	Serial.print(F(","));
	Serial.println(this->gyro_z);
}


double MP_LSM6DS3::getAccel_X()
{
	return this->accel_x;
}

double MP_LSM6DS3::getAccel_Y()
{
	return this->accel_y;
}

double MP_LSM6DS3::getAccel_Z()
{
	return this->accel_z;
}

double MP_LSM6DS3::getAccel_Magnitude()
{
	return this->accel_mag;
}

double MP_LSM6DS3::getGyro_X()
{
	return this->gyro_x;
}

double MP_LSM6DS3::getGyro_Y()
{
	return this->gyro_y;
}

double MP_LSM6DS3::getGyro_Z()
{
	return this->gyro_z;
}
