#include "MP_PAH8001EI2G_Seeed.h"

MP_PAH8001EI2G_Seeed::MP_PAH8001EI2G_Seeed()
{
}

int MP_PAH8001EI2G_Seeed::init()
{
    Wire.begin();
	return MP_ERR_OK;
}

void MP_PAH8001EI2G_Seeed::update(unsigned long current_time) 
{
	if (current_time - lastMillis > 1000)
	{
        Wire.requestFrom(0xA0 >> 1, 1);
        while(Wire.available())
        {
            this->heartRate = Wire.read();
        }
		lastMillis = current_time;
	}
}

void MP_PAH8001EI2G_Seeed::printStatus()
{
	Serial.print(F("heartrate = "));
	Serial.print(this->heartRate);
}


double MP_PAH8001EI2G_Seeed::getHeart_Rate()
{
	return this->heartRate;
}