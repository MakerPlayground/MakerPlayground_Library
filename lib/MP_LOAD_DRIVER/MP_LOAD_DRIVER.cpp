#include "MP_LOAD_DRIVER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_LOAD_DRIVER::ERRORS = errors_p;

MP_LOAD_DRIVER::MP_LOAD_DRIVER(uint8_t pin)
	:pin(pin)
{
}

int MP_LOAD_DRIVER::init()
{
	pinMode(pin, OUTPUT);
	isOn = false;
	return 0;
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
