#include "MP_LOAD_DRIVER_AL.h"

MP_LOAD_DRIVER_AL::MP_LOAD_DRIVER_AL(uint8_t pin)
	:pin(pin)
{
}

int MP_LOAD_DRIVER_AL::init()
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	isOn = false;
	return MP_ERR_OK;
}

void MP_LOAD_DRIVER_AL::update(unsigned long current_time) 
{

}

void MP_LOAD_DRIVER_AL::printStatus()
{
	Serial.print(F("Status is now "));
	Serial.println(this->isOn ? "On" : "Off");
}

void MP_LOAD_DRIVER_AL::on()
{
	this->isOn = true;
	digitalWrite(pin, LOW);
}

void MP_LOAD_DRIVER_AL::off()
{
	this->isOn = false;
	digitalWrite(pin, HIGH);
}
