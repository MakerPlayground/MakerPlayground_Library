#include "MP_SOIL_MOISTURE.h"

MP_SOIL_MOISTURE::MP_SOIL_MOISTURE(uint8_t data, uint8_t en,const String &tag)
	:data(data)
	,en(en)
	,tag(tag)
{
}

void MP_SOIL_MOISTURE::init()
{
	pinMode(data, INPUT);
	pinMode(en, OUTPUT);
}

double MP_SOIL_MOISTURE::getPercent()
{
	digitalWrite(en, HIGH);
	delay(5);
	double value = (analogRead(data) / 1023.0) * 100.0;
	digitalWrite(en, LOW);
	return value;
}
