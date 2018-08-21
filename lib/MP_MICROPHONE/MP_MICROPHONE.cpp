#include "MP_MICROPHONE.h"

MP_MP_MICROPHONE::MP_MP_MICROPHONE(uint8_t pin,const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_MP_MICROPHONE::init()
{
	pinMode(pin, INPUT);
}

double MP_MP_MICROPHONE::getSoundLevel()
{
	Serial.println(100.0*analogRead(pin)/1024.0);
	return 100.0*analogRead(pin)/1024.0;
}
