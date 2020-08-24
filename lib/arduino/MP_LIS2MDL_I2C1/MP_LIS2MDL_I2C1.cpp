#include "MP_LIS2MDL_I2C1.h"

#define PI 3.14159

MP_LIS2MDL_I2C1::MP_LIS2MDL_I2C1()
{
}

int MP_LIS2MDL_I2C1::init()
{
	end_time = 0;
	Wire1.begin(4, 5);
	lis2mdl.enableAutoRange(true);
	if(!lis2mdl.begin(0x1E, &Wire1)) {
		return MP_ERR_CONNECT_DEVICE;
	}
	return MP_ERR_OK;
}

void MP_LIS2MDL_I2C1::update(unsigned long current_time) 
{
	if (current_time - end_time > 10) {
		sensors_event_t event;
        lis2mdl.getEvent(&event);
		this->mag_x = event.magnetic.x;
		this->mag_y = event.magnetic.y;
		this->mag_z = event.magnetic.z;
		float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / PI;
        // Normalize to 0-360
        if (heading < 0) {
            heading = 360 + heading;
        }
		this->heading = heading;
		end_time = current_time;
	}
}

void MP_LIS2MDL_I2C1::printStatus()
{
	Serial.print(F("x,y,z,heading = "));
	Serial.print(this->mag_x);

	Serial.print(F(","));
	Serial.print(this->mag_y);
	
	Serial.print(F(","));
	Serial.print(this->mag_z);

	Serial.print(F(","));
    Serial.print(this->heading);
}


double MP_LIS2MDL_I2C1::getMag_X()
{
	return this->mag_x;
}

double MP_LIS2MDL_I2C1::getMag_Y()
{
	return this->mag_y;
}

double MP_LIS2MDL_I2C1::getMag_Z()
{
	return this->mag_z;
}

double MP_LIS2MDL_I2C1::getHeading()
{
    return this->heading;
}

bool MP_LIS2MDL_I2C1::checkDirection(uint8_t direction)
{
    double minDegree = (direction * 45.0) - 22.5;
    double maxDegree = (direction * 45.0) + 22.5;
    return (heading >= minDegree && heading <= maxDegree);
}