#include "MP_LIS3DH_WioTerminal.h"

MP_LIS3DH_WioTerminal::MP_LIS3DH_WioTerminal()
{
}

int MP_LIS3DH_WioTerminal::init()
{
	end_time = 0;
	lis.begin(Wire1);
	if (!lis) {
	    return MP_ERR_CONNECT_DEVICE;
	}
    delay(100);
    lis.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
    lis.setFullScaleRange(LIS3DHTR_RANGE_4G);
	return MP_ERR_OK;
}

void MP_LIS3DH_WioTerminal::update(unsigned long current_time) 
{
	if (current_time - end_time > 20) {
		this->accel_x = lis.getAccelerationX();
		this->accel_y = lis.getAccelerationY();
		this->accel_z = lis.getAccelerationZ();
		this->accel_mag = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z);
		end_time = current_time;
	}
}

void MP_LIS3DH_WioTerminal::printStatus()
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

double MP_LIS3DH_WioTerminal::getAccel_X()
{
	return this->accel_x;
}

double MP_LIS3DH_WioTerminal::getAccel_Y()
{
	return this->accel_y;
}

double MP_LIS3DH_WioTerminal::getAccel_Z()
{
	return this->accel_z;
}

double MP_LIS3DH_WioTerminal::getAccel_Magnitude()
{
	return this->accel_mag;
}