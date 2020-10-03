#include "MP_LIS3DHTR.h"

#define GRAVITY 9.80665

MP_LIS3DHTR::MP_LIS3DHTR()
{
}

int MP_LIS3DHTR::init()
{
	end_time = 0;
  lis.begin(Wire, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  if (!lis) {
	  return MP_ERR_CONNECT_DEVICE;
	}
  lis.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
	lis.setFullScaleRange(LIS3DHTR_RANGE_4G);
	return MP_ERR_OK;
}

void MP_LIS3DHTR::update(unsigned long current_time) 
{
	if (current_time - end_time > 20) {
		this->accel_x = lis.getAccelerationX() * GRAVITY;
		this->accel_y = lis.getAccelerationY() * GRAVITY;
		this->accel_z = lis.getAccelerationZ() * GRAVITY;
		this->accel_mag = sqrt(this->accel_x * this->accel_x + this->accel_y * this->accel_y + this->accel_z * this->accel_z);
		end_time = current_time;
	}
}

void MP_LIS3DHTR::printStatus()
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

double MP_LIS3DHTR::getAccel_X()
{
	return this->accel_x;
}

double MP_LIS3DHTR::getAccel_Y()
{
	return this->accel_y;
}

double MP_LIS3DHTR::getAccel_Z()
{
	return this->accel_z;
}

double MP_LIS3DHTR::getAccel_Magnitude()
{
	return this->accel_mag;
}