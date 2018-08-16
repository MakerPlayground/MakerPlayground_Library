#include "MP_LED_AH.h"

MP_LED_AH::MP_LED_AH(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_LED_AH::init()
{
	pinMode(this->pin, OUTPUT);
}

void MP_LED_AH::on(int brightness)
{
	analogWrite(this->pin, map(brightness, 0, 100, 0, 255));
}

void MP_LED_AH::off()
{
	digitalWrite(this->pin,LOW);
}