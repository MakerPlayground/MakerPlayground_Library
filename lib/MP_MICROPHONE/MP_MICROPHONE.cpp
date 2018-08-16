#include "MP_MICROPHONE.h"

MP_MICROPHONE::MP_MICROPHONE(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_MICROPHONE::init()
{
	pinMode(this->pin, INPUT);
	normal = analogRead(pin);
	for(int i=1; i<MP_MICROPHONE_MAX_ARRAY; i++)
	{
		normal = 0.8 * normal + 0.2 * (analogRead(pin) - normal);
	}
}

double MP_MICROPHONE::getSoundLevel()
{
	double max = 0;
    double min = 1024;
    for (int i=0; i<MP_MICROPHONE_MAX_ARRAY; i++) {
        normal = 0.8 * normal + 0.2 * (analogRead(pin) - normal);
        delayMicroseconds(200);
        if (normal > max) max = normal;
        if (normal < min) min = normal;
	}
	double val = (fabs(max - min) - 100.0) / 300.0 * 100.0;
	if (val > 100) val = 100;
	else if (val < 0) val = 0;
	return val;
}
