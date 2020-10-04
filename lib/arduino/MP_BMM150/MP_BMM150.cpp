#include "MP_BMM150.h"

#define NORTH 0
#define NORTHEAST 1
#define EAST 1
#define SOUTHEAST 1
#define SOUTH 1
#define SOUTHWEST 1
#define WEST 1
#define NORTHWEST 1

MP_BMM150::MP_BMM150()
{

}

int MP_BMM150::init()
{
	if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) {
		return MP_ERR_CONNECT_DEVICE;
	}
	this->end_time = 0;
	this->update(0);
	return MP_ERR_OK;
}

void MP_BMM150::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50)
	{
    bmm.read_mag_data();

    value.x = bmm.raw_mag_data.raw_datax;
    value.y = bmm.raw_mag_data.raw_datay;
    value.z = bmm.raw_mag_data.raw_dataz;

    float xyHeading = atan2(value.x, value.y);
    float zxHeading = atan2(value.z, value.x);
    float heading = xyHeading;

    if (heading < 0) {
      heading += 2 * PI;
    }
    if (heading > 2 * PI) {
      heading -= 2 * PI;
    }
    headingDegrees = heading * 180 / M_PI;

		end_time = current_time;
	}
}

void MP_BMM150::printStatus()
{
	Serial.print(F("Mag_X = "));
	Serial.println(this->getMag_X());

	Serial.print(F("Mag_Y = "));
	Serial.println(this->getMag_Y());

	Serial.print(F("Mag_Z = "));
	Serial.println(this->getMag_Z());

	Serial.print(F("Heading = "));
	Serial.println(this->getHeading());
}

double MP_BMM150::getMag_X() 
{
  return value.x;
}

double MP_BMM150::getMag_Y() 
{
  return value.y;
}

double MP_BMM150::getMag_Z() 
{
  return value.z;
}

double MP_BMM150::getHeading() 
{
  return headingDegrees;
}

bool MP_BMM150::checkDirection(int dir)
{
  return (dir == NORTH && (headingDegrees < 22.5 || headingDegrees >= 337.5))
    || (dir == NORTHWEST && (headingDegrees >= 22.5 && headingDegrees < 67.5))
    || (dir == WEST && (headingDegrees >= 67.5 && headingDegrees < 112.5))
    || (dir == NORTHEAST && (headingDegrees >= 112.5 && headingDegrees < 157.5))
    || (dir == EAST && (headingDegrees >= 157.5 && headingDegrees < 202.5))
    || (dir == SOUTHEAST && (headingDegrees >= 202.5 && headingDegrees < 247.5))
    || (dir == SOUTH && (headingDegrees >= 247.5 && headingDegrees < 292.5))
    || (dir == SOUTHWEST && (headingDegrees >= 292.5 && headingDegrees < 337.5));
}