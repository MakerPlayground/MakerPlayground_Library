#include "MP_PMS7003_SERIAL2.h"

MP_PMS7003_SERIAL2::MP_PMS7003_SERIAL2()
	: pms(Serial2)
	, isDataCorrected(false)
	, lastReadSuccess(0)
{
}

int MP_PMS7003_SERIAL2::init()
{
    Serial2.begin(9600);
	pms.activeMode();
	return MP_ERR_OK;
}

void MP_PMS7003_SERIAL2::update(unsigned long current_time)
{
    if (pms.read(data))
    {
		lastReadSuccess = current_time;
		isDataCorrected = true;
	}
	else if (current_time - lastReadSuccess > 2400)  // Data is update not slower than 2.3s
	{
		isDataCorrected = false;
	}
}

bool MP_PMS7003_SERIAL2::isDataValid()
{
	return isDataCorrected;
}

bool MP_PMS7003_SERIAL2::isDataInvalid()
{
	return !isDataCorrected;
}

void MP_PMS7003_SERIAL2::printStatus()
{
	if (isDataCorrected)
	{
		Serial.print(F("PM1.0 = "));
		Serial.print(data.PM_AE_UG_1_0);
		Serial.print(F("ug/m^3 "));
		Serial.print(F("PM2.5 = "));
		Serial.print(data.PM_AE_UG_2_5);
		Serial.print(F("ug/m^3 "));
		Serial.print(F("PM10 = "));
		Serial.print(data.PM_AE_UG_10_0);
		Serial.print(F("ug/m^3 "));
	}
	else
	{
		Serial.print(F("Data from sensor is not valid"));
	}
}

uint16_t MP_PMS7003_SERIAL2::getAtmospheric_PM_1_0()
{
	return data.PM_AE_UG_1_0;
}

uint16_t MP_PMS7003_SERIAL2::getAtmospheric_PM_2_5()
{
	return data.PM_AE_UG_2_5;
}

uint16_t MP_PMS7003_SERIAL2::getAtmospheric_PM_10()
{
	return data.PM_AE_UG_10_0;
}
