#include "MP_RELAY.h"

MP_RELAY::MP_RELAY(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_RELAY::init()
{
	pinMode(pin, OUTPUT);
}

void MP_RELAY::on()
{
	digitalWrite(pin, HIGH);
}

void MP_RELAY::off()
{
	digitalWrite(pin, LOW);
}
