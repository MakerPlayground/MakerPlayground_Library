#include "MP_LOAD_DRIVER.h"

MP_LOAD_DRIVER::MP_LOAD_DRIVER(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_LOAD_DRIVER::init()
{
	pinMode(pin, OUTPUT);
}

void MP_LOAD_DRIVER::on()
{
	digitalWrite(pin, HIGH);
}

void MP_LOAD_DRIVER::off()
{
	digitalWrite(pin, LOW);
}
