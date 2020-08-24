#include "MP_SOIL_MOISTURE_W_EN.h"

MP_SOIL_MOISTURE_W_EN::MP_SOIL_MOISTURE_W_EN(uint8_t data, uint8_t en)
	:data(data)
	,en(en)
{
}

int MP_SOIL_MOISTURE_W_EN::init()
{
	pinMode(data, INPUT);
	pinMode(en, OUTPUT);
	digitalWrite(en, HIGH);
	return MP_ERR_OK;
}

void MP_SOIL_MOISTURE_W_EN::update(unsigned long current_time)
{
	this->value = (analogRead(data) / 1023.0) * 100.0;
}

void MP_SOIL_MOISTURE_W_EN::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_SOIL_MOISTURE_W_EN::getPercent()
{
	return this->value;
}