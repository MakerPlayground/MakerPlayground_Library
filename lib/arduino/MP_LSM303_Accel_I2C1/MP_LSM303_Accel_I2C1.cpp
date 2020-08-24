#include "MP_LSM303_Accel_I2C1.h"

MP_LSM303_Accel_I2C1::MP_LSM303_Accel_I2C1()
{
}

int MP_LSM303_Accel_I2C1::init()
{
	end_time = 0;
	Wire1.begin(4, 5);
	if(!accel.begin(LSM303_ADDRESS_ACCEL, &Wire1)) {
		return MP_ERR_CONNECT_DEVICE;
	}
	accel.setRange(LSM303_RANGE_4G);
	accel.setMode(LSM303_MODE_NORMAL);
	return MP_ERR_OK;
}

void MP_LSM303_Accel_I2C1::update(unsigned long current_time) 
{
	if (current_time - end_time > 10) {
		sensors_event_t event;
        accel.getEvent(&event);
		this->accel_x = event.acceleration.x;
		this->accel_y = event.acceleration.y;
		this->accel_z = event.acceleration.z;
		this->accel_mag = sqrt(this->accel_x * this->accel_x + this->accel_y * this->accel_y + this->accel_z * this->accel_z);
		end_time = current_time;
	}
}

void MP_LSM303_Accel_I2C1::printStatus()
{
	Serial.print(F("ax,ay,az,amag = "));
	Serial.print(this->accel_x);

	Serial.print(F(","));
	Serial.print(this->accel_y);
	
	Serial.print(F(","));
	Serial.print(this->accel_z);
	
	Serial.print(F(","));
	Serial.print(this->accel_mag);
}


double MP_LSM303_Accel_I2C1::getAccel_X()
{
	return this->accel_x;
}

double MP_LSM303_Accel_I2C1::getAccel_Y()
{
	return this->accel_y;
}

double MP_LSM303_Accel_I2C1::getAccel_Z()
{
	return this->accel_z;
}

double MP_LSM303_Accel_I2C1::getAccel_Magnitude()
{
	return this->accel_mag;
}