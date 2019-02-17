#include "MP_WINSEN_ZH03.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_WINSEN_ZH03::ERRORS = errors_p;

#define Q_INTERVAL 100

MP_WINSEN_ZH03::MP_WINSEN_ZH03(uint8_t dust_tx, uint8_t dust_rx, int baud)
	: ss(SoftwareSerial(dust_tx, dust_rx))
	, dustBaud(baud)
	, PM1_0(0)
	, PM2_5(0)
	, PM10(0)
	, isDataCorrected(false)
{
}

int MP_WINSEN_ZH03::init()
{
	ss.begin(dustBaud);
	for(int i=0; i<10; i++)
	{
        ss.write(configCommand[i]);
    }
	return 0;
}

void MP_WINSEN_ZH03::update(unsigned long current_time)
{
    if (current_time - lastQMillis >= Q_INTERVAL)
    {
        for(int i = 0; i<10; i++)
        {
            ss.write(sensorCommand[i]);
        }

        if (ss.readBytes(data, 9) == 9 && data[0] == 0xFF && data[1] == 0x86)
        {
			PM1_0 = (data[6] * 256) + data[7];
            PM2_5 = (data[2] * 256) + data[3];
			PM10 = (data[4] * 256) + data[5];
            isDataCorrected = true;
        }
        else
        {
            isDataCorrected = false;
        }

        lastQMillis = current_time;
    }
}

bool MP_WINSEN_ZH03::isDataValid()
{
	return isDataCorrected;
}

bool MP_WINSEN_ZH03::isDataInvalid()
{
	return !isDataCorrected;
}

void MP_WINSEN_ZH03::printStatus()
{
	if (isDataCorrected)
	{
		Serial.print(F("PM1.0 = "));
		Serial.print(PM1_0);
		Serial.println(F("ug/m^3"));

		Serial.print(F("PM2.5 = "));
		Serial.print(PM2_5);
		Serial.println(F("ug/m^3"));

		Serial.print(F("PM10 = "));
		Serial.print(PM10);
		Serial.println(F("ug/m^3"));
	}
	else
	{
		Serial.print(F("Data from sensor is not valid"));
	}
}

uint16_t MP_WINSEN_ZH03::getAtmospheric_PM_1_0()
{
	return PM1_0;
}

uint16_t MP_WINSEN_ZH03::getAtmospheric_PM_2_5()
{
	return PM2_5;
}

uint16_t MP_WINSEN_ZH03::getAtmospheric_PM_10()
{
	return PM10;
}
