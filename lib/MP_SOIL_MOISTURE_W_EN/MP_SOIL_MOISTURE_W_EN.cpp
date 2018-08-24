#include "MP_SOIL_MOISTURE_W_EN.h"

MP_SOIL_MOISTURE_W_EN::MP_SOIL_MOISTURE_W_EN(uint8_t data, uint8_t en,const String &tag)
	:data(data)
	,en(en)
	,tag(tag)
{
}

void MP_SOIL_MOISTURE_W_EN::init()
{
	pinMode(data, INPUT);
	pinMode(en, OUTPUT);
}

double MP_SOIL_MOISTURE_W_EN::getPercent()
{
	digitalWrite(en, HIGH);
	delay(5);
	double value = (analogRead(data) / 1023.0) * 100.0;
	digitalWrite(en, LOW);
	return value;
}
