#include "MP_MCP9700.h"

MP_MCP9700::MP_MCP9700(uint8_t pin)
	:pin(pin)
{
}

int MP_MCP9700::init()
{
	pinMode(pin, INPUT);
    digitalWrite(pin, LOW);
	return MP_ERR_OK;
}

void MP_MCP9700::update(unsigned long current_time)
{
#if defined(ESP8266) || defined(ESP32)
	this->value = (analogRead(pin) / 1023.0 * 330) - 50;
#else
    this->value = (analogRead(pin) / 1023.0 * 500) - 50;
#endif
}

void MP_MCP9700::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_MCP9700::getTemperature()
{
	return value;
}
