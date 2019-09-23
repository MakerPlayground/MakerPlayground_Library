#include "MP_RELAY_AL.h"

MP_RELAY_AL::MP_RELAY_AL(uint8_t pin)
	:pin(pin)
{
}

int MP_RELAY_AL::init()
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	this->isOn = false;
	return ERR_OK;
}

void MP_RELAY_AL::update(unsigned long current_time)
{

}

void MP_RELAY_AL::printStatus()
{
	Serial.print(F("status = "));
	Serial.println(this->isOn ? "on": "off");
}

void MP_RELAY_AL::on()
{
	this->isOn = true;
	digitalWrite(pin, LOW);
}

void MP_RELAY_AL::off()
{
	this->isOn = false;
	digitalWrite(pin, HIGH);
}
