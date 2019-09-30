#include "MP_BH1750.h"

#define UPDATE_INTERVAL 1000

MP_BH1750::MP_BH1750(bool addr_pull_up)
	:lightMeter(addr_pull_up ? 0x5C : 0x23)
	, percent(0)
	, lux(0)
{
}

int MP_BH1750::init()
{
	Wire.begin();
	if(!lightMeter.begin())
	{
		return ERR_CONNECT_DEVICE;
	}
	return ERR_OK;
}

void MP_BH1750::update(unsigned long current_time)
{
	if (current_time - last_update > UPDATE_INTERVAL) {
		lux = lightMeter.readLightLevel();
		if (lux < 0) {
			percent = 0.0;
		}
		else if (lux > 50000) { // tested on mobile phone flash
			percent = 100.0;
		}
		else {
			percent = lux / 500.0;
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

double MP_BH1750::getIntensity()
{
	return lux;
}