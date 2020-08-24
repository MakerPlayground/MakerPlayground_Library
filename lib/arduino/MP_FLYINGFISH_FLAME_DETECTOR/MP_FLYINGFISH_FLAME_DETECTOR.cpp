#include "MP_FLYINGFISH_FLAME_DETECTOR.h"

MP_FLYINGFISH_FLAME_DETECTOR::MP_FLYINGFISH_FLAME_DETECTOR(uint8_t pin)
	:pin(pin)
{
}

int MP_FLYINGFISH_FLAME_DETECTOR::init()
{
	pinMode(this->pin, INPUT);
	return MP_ERR_OK;
}

void MP_FLYINGFISH_FLAME_DETECTOR::printStatus()
{
    Serial.print(F("percent = "));
	Serial.println(percent);
}

void MP_FLYINGFISH_FLAME_DETECTOR::update(unsigned long time)
{
    percent = 100.0 - (analogRead(pin)/1023.0)*100;
}

double MP_FLYINGFISH_FLAME_DETECTOR::getPercent()
{
	return percent;
}
