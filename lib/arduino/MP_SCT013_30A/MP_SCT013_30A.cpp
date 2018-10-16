#include "MP_SCT013_30A.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_SCT013_30A::ERRORS = errors_p;

MP_SCT013_30A::MP_SCT013_30A(uint8_t pin)
	: pin(pin)
	, value(0)
	, maxValue(0)
	, lastReadingTime(0)
	, nextResetTime(0)
{
}

int MP_SCT013_30A::init()
{
	pinMode(this->pin, INPUT);
	return 0;
}

void MP_SCT013_30A::update(unsigned long currentTime)
{
    if (lastReadingTime <= currentTime) {
        int tmp = analogRead(pin);
        if (tmp > maxValue) {
            maxValue = tmp;
        }
        lastReadingTime = currentTime + 5;
    }

    if (nextResetTime <= currentTime) {
        value = (maxValue / 204.6) * 30.0 / 1.4142; // 0-1V -> 0-30A
        maxValue = 0;
        nextResetTime = currentTime + 1000; // refresh current value every 1 second
    }
}

double MP_SCT013_30A::getAmpere()
{
	return this->value;
}

void MP_SCT013_30A::printStatus()
{
	Serial.print(F("Value = "));
	Serial.print(this->value);
}