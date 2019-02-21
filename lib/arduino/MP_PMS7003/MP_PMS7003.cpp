#include "MP_PMS7003.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_PMS7003::ERRORS = errors_p;


MP_PMS7003::MP_PMS7003(uint8_t dust_tx, uint8_t dust_rx, int baud)
	: ss(SoftwareSerial(dust_tx, dust_rx))
	, pms(ss)
	, isDataCorrected(false)
{
}

int MP_PMS7003::init()
{
	pms.activeMode();
	return 0;
}

void MP_PMS7003::update(unsigned long current_time)
{
    if (pms.read(data)) {
		lastReadSuccess = current_time;
		isDataCorrected = true;
	}
	else if (current_time - lastReadSuccess > 2400)  // Data is update not slower than 2.3s
	{
		isDataCorrected = false;
	}
}

bool MP_PMS7003::isDataValid()
{
	return isDataCorrected;
}

bool MP_PMS7003::isDataInvalid()
{
	return !isDataCorrected;
}

void MP_PMS7003::printStatus()
{
	if (isDataCorrected)
	{
		Serial.print(F("PM1.0 = "));
		Serial.print(data.PM_AE_UG_1_0);
		Serial.println(F("ug/m^3"));
		Serial.print(F("PM2.5 = "));
		Serial.print(data.PM_AE_UG_2_5);
		Serial.println(F("ug/m^3"));
		Serial.print(F("PM10 = "));
		Serial.print(data.PM_AE_UG_10_0);
		Serial.println(F("ug/m^3"));
	}
	else
	{
		Serial.print(F("Data from sensor is not valid"));
	}
}

uint16_t MP_PMS7003::getAtmospheric_PM_1_0()
{
	return data.PM_AE_UG_1_0;
}

uint16_t MP_PMS7003::getAtmospheric_PM_2_5()
{
	return data.PM_AE_UG_2_5;
}

uint16_t MP_PMS7003::getAtmospheric_PM_10()
{
	return data.PM_AE_UG_10_0;
}