#include "MP_L3GD20H.h"

MP_L3GD20H::MP_L3GD20H(const String &tag)
	:tag(tag)
{
}

void MP_L3GD20H::init()
{
	/* Enable auto-ranging */
	gyro.enableAutoRange(true);

	/* Initialise the sensor */
	if (!gyro.begin())
	{
		/* There was a problem detecting the L3GD20 ... check your connections */
		// Serial.println("Could not find a valid L3GD20 sensor, check wiring!");
		while (1);
	}
}

double MP_L3GD20H::getGyro_X()
{
	gyro.getEvent(&event);
	return event.gyro.x * PI;
}

double MP_L3GD20H::getGyro_Y()
{
	gyro.getEvent(&event);
	return event.gyro.y * PI;
}

double MP_L3GD20H::getGyro_Z()
{
	gyro.getEvent(&event);
	return event.gyro.z * PI;
}
