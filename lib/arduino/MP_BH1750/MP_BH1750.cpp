#include "MP_BH1750.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't connect to BH1750";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_BH1750::ERRORS = errors_p;

#define UPDATE_INTERVAL 100

MP_BH1750::MP_BH1750(bool addr_pull_up)
	:lightMeter(addr_pull_up ? 0x5C : 0x23)
{
}

int MP_BH1750::init()
{
	if(!lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
	{
		return 1;
	}
	return 0;
}

void MP_BH1750::update(unsigned long current_time)
{
	if (current_time - last_update > UPDATE_INTERVAL) {
		lux = lightMeter.readLightLevel();
		if (lux < 0) {
			percent = 0.0;
		}
		else {
			percent = lux / 5000.0;  // This could not be a magic number. -> Change later
		}
		last_update = current_time;
	}
}

void MP_BH1750::printStatus()
{
	Serial.print(F("Percent = "));
	Serial.println(percent);
}

double MP_BH1750::getPercent()
{
	return percent;
}