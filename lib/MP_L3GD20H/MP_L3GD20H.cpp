#include "MP_L3GD20H.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Could not find a valid L3GD20 sensor, check wiring!";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_L3GD20H::ERRORS = errors_p;

MP_L3GD20H::MP_L3GD20H()
{
}

int MP_L3GD20H::init()
{
	/* Enable auto-ranging */
	gyro.enableAutoRange(true);

	/* Initialise the sensor */
	if (!gyro.begin()) {
		return 1;
	}

	this->end_time = 0;
	this->update(0);
	return 0;
}

void MP_L3GD20H::update(unsigned long current_time)
{
	if (end_time == 0 || current_time - end_time > 50) {
		gyro.getEvent(&event);
		end_time = current_time;
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
	return event.gyro.x * PI;
}

double MP_L3GD20H::getGyro_Y()
{
	return event.gyro.y * PI;
}

double MP_L3GD20H::getGyro_Z()
{
	return event.gyro.z * PI;
}
