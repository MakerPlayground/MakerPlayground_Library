#include "MP_RELAY.h"

MP_RELAY::MP_RELAY(uint8_t pin)
	:pin(pin)
{
}

int MP_RELAY::init()
{
	pinMode(pin, OUTPUT);
	this->isOn = false;
	return MP_ERR_OK;
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
