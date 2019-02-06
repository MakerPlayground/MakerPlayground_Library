#include "MP_DUST.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_DUST::ERRORS = errors_p;

#define Q_INTERVAL 100

MP_DUST::MP_DUST(uint8_t dust_tx, uint8_t dust_rx, int baud)
	: ss(SoftwareSerial(dust_tx, dust_rx))
	, dustBaud(baud)
	, PM25(0)
	, isDataCorrected(false)
{
}

int MP_DUST::init()
{
	ss.begin(dustBaud);
	for(int i=0; i<10; i++)
	{
        ss.write(configCommand[i]);
    }
	return 0;
}

void MP_DUST::update(unsigned long current_time)
{
    if (current_time - lastQMillis >= Q_INTERVAL)
    {
        for(int i = 0; i<10; i++)
        {
            ss.write(sensorCommand[i]);
        }

        if (ss.readBytes(data, 9) == 9 && data[0] == 0xFF && data[1] == 0x86)
        {
            PM25 = (data[2] * 256) + data[3];
            isDataCorrected = true;
        }
        else
        {
             isDataCorrected = false;
        }

        lastQMillis = current_time;
    }
}

bool MP_DUST::isDataValid()
{
	return isDataCorrected;
}

bool MP_DUST::isDataInvalid()
{
	return !isDataCorrected;
}

void MP_DUST::printStatus()
{
	if (isDataCorrected)
	{
		Serial.print(F("PM2.5 = "));
		Serial.print(PM25);
	}
	else
	{
		Serial.print(F("Data from sensor is not valid"));
	}
}

double MP_DUST::getPM_2_5()
{
	return PM25;
}
