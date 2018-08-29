#include "MP_RELAY.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_RELAY::ERRORS = errors_p;

MP_RELAY::MP_RELAY(uint8_t pin)
	:pin(pin)
{
}

int MP_RELAY::init()
{
	pinMode(pin, OUTPUT);
	this->isOn = false;
	return 0;
}

void MP_RELAY::update(unsigned long current_time)
{

}

void MP_RELAY::printStatus()
{
	Serial.print(F("status = "));
	Serial.println(this->isOn ? "on": "off");
}

void MP_RELAY::on()
{
	this->isOn = true;
	digitalWrite(pin, HIGH);
}

void MP_RELAY::off()
{
	this->isOn = false;
	digitalWrite(pin, LOW);
}
