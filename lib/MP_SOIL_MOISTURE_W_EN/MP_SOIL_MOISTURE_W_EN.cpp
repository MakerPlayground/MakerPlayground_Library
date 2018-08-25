#include "MP_SOIL_MOISTURE_W_EN.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_SOIL_MOISTURE_W_EN::ERRORS = errors_p;

MP_SOIL_MOISTURE_W_EN::MP_SOIL_MOISTURE_W_EN(uint8_t data, uint8_t en)
	:data(data)
	,en(en)
{
}

void MP_SOIL_MOISTURE_W_EN::init()
{
	pinMode(data, INPUT);
	pinMode(en, OUTPUT);
}

void MP_SOIL_MOISTURE::update(unsigned long current_time)
{
	digitalWrite(en, HIGH);
	delay(5);
	this->value = (analogRead(data) / 1023.0) * 100.0;
	digitalWrite(en, LOW);
}

void MP_SOIL_MOISTURE::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_SOIL_MOISTURE::getPercent()
{
	return this->value;
}