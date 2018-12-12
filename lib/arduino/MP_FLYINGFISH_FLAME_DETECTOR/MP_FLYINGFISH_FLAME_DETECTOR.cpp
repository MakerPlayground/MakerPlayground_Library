#include "MP_FLYINGFISH_FLAME_DETECTOR.h"
const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_FLYINGFISH_FLAME_DETECTOR::ERRORS = errors_p;

MP_FLYINGFISH_FLAME_DETECTOR::MP_FLYINGFISH_FLAME_DETECTOR(uint8_t pin)
	:pin(pin)
{
}

int MP_FLYINGFISH_FLAME_DETECTOR::init()
{
	pinMode(this->pin, INPUT);
	return 0;
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
