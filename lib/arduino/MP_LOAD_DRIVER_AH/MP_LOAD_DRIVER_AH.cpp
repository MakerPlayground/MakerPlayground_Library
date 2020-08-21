#include "MP_LOAD_DRIVER_AH.h"

MP_LOAD_DRIVER_AH::MP_LOAD_DRIVER_AH(uint8_t pin)
	:pin(pin)
{
}

int MP_LOAD_DRIVER_AH::init()
{
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	isOn = false;
	return ERR_OK;
}

void MP_LOAD_DRIVER_AH::update(unsigned long current_time) 
{

}

void MP_LOAD_DRIVER_AH::printStatus()
{
	Serial.print(F("Status is now "));
	Serial.println(this->isOn ? "On" : "Off");
}

void MP_LOAD_DRIVER_AH::on()
{
	this->isOn = true;
	digitalWrite(pin, HIGH);
}

void MP_LOAD_DRIVER_AH::off()
{
	this->isOn = false;
	digitalWrite(pin, LOW);
}
