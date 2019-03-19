#include "MP_LOAD_DRIVER.h"

MP_LOAD_DRIVER::MP_LOAD_DRIVER(uint8_t pin)
	:pin(pin)
{
}

int MP_LOAD_DRIVER::init()
{
	pinMode(pin, OUTPUT);
	isOn = false;
	return ERR_OK;
}

void MP_LOAD_DRIVER::update(unsigned long current_time) 
{

}

void MP_LOAD_DRIVER::printStatus()
{
	Serial.print(F("Status is now "));
	Serial.println(this->isOn ? "On" : "Off");
}

void MP_LOAD_DRIVER::on()
{
	this->isOn = true;
	digitalWrite(pin, HIGH);
}

void MP_LOAD_DRIVER::off()
{
	this->isOn = false;
	digitalWrite(pin, LOW);
}
