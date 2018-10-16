#include "MP_SCT013_30A_ESP32.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_SCT013_30A_ESP32::ERRORS = errors_p;

MP_SCT013_30A_ESP32::MP_SCT013_30A_ESP32(uint8_t pin)
	: pin(pin)
	, value(0)
	, maxValue(0)
	, lastReadingTime(0)
	, nextResetTime(0)
{
}

int MP_SCT013_30A_ESP32::init()
{
	pinMode(this->pin, INPUT);
	analogReadResolution(10);
    analogSetWidth(10);
  	analogSetPinAttenuation(this->pin, ADC_0db);	// acceptable range from 0-1v
	return 0;
}

void MP_SCT013_30A_ESP32::update(unsigned long currentTime)
{
    int tmp = analogRead(pin);
    if (tmp > maxValue) {
        maxValue = tmp;
    }

    if (nextResetTime <= currentTime) {
        value = (maxValue / 930.0) * 30.0 / 1.4142; // 0-1V -> 0-30A
        maxValue = 0;
        nextResetTime = currentTime + 1000; // refresh current value every 1 second
    }
}

double MP_SCT013_30A_ESP32::getAmpere()
{
	return this->value;
}

void MP_SCT013_30A_ESP32::printStatus()
{
	Serial.print(F("Value = "));
	Serial.print(this->value);
}