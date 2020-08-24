#include "MP_SCT013_30A_ESP32.h"

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
  	analogSetPinAttenuation(this->pin, ADC_0db);	// acceptable range from 0-1v
	return MP_ERR_OK;
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