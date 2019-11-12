#include "MP_L3GD20H.h"

MP_L3GD20H::MP_L3GD20H()
{
}

int MP_L3GD20H::init()
{
	/* Enable auto-ranging */
	gyro.enableAutoRange(true);

	/* Initialise the sensor */
	if (!gyro.begin()) {
		return ERR_CONNECT_DEVICE;
	}

	this->end_time = 0;
	this->update(0);
	return ERR_OK;
}

void MP_L3GD20H::update(unsigned long current_time)
{
	if (end_time == 0 || current_time - end_time > 50) {
		gyro.getEvent(&event);
		end_time = current_time;
		event.gyro.x *= PI;
		event.gyro.y *= PI;
		event.gyro.z *= PI;
	}
}

void MP_L3GD20H::printStatus()
{
	Serial.print(F("gyro_x = "));
	Serial.println(this->getGyro_X());

	Serial.print(F("gyro_y = "));
	Serial.println(this->getGyro_Y());

	Serial.print(F("gyro_z = "));
	Serial.println(this->getGyro_Z());
}

double MP_L3GD20H::getGyro_X()
{
	return event.gyro.x;
}

double MP_L3GD20H::getGyro_Y()
{
	return event.gyro.y;
}

double MP_L3GD20H::getGyro_Z()
{
	return event.gyro.z;
}
