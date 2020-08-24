#include "MP_LIS3DH.h"

MP_LIS3DH::MP_LIS3DH()
	:lis(Adafruit_LIS3DH())
{
}

int MP_LIS3DH::init()
{
	end_time = 0;
	if(!lis.begin(0x18)) {
		return MP_ERR_CONNECT_DEVICE;
	}
	lis.setRange(LIS3DH_RANGE_4_G);
	return MP_ERR_OK;
}

void MP_LIS3DH::update(unsigned long current_time) 
{
	if (current_time - end_time > 10) {
		sensors_event_t event; 
		lis.getEvent(&event);
		this->accel_x = event.acceleration.x;
		this->accel_y = event.acceleration.y;
		this->accel_z = event.acceleration.z;
		this->accel_mag = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
		end_time = current_time;
	}
}

void MP_LIS3DH::printStatus()
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


double MP_LIS3DH::getAccel_X()
{
	return this->accel_x;
}

double MP_LIS3DH::getAccel_Y()
{
	return this->accel_y;
}

double MP_LIS3DH::getAccel_Z()
{
	return this->accel_z;
}

double MP_LIS3DH::getAccel_Magnitude()
{
	return this->accel_mag;
}