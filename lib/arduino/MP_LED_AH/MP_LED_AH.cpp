#include "MP_LED_AH.h"

MP_LED_AH::MP_LED_AH(uint8_t pin)
	:pin(pin)
{
}

int MP_LED_AH::init()
{
	pinMode(this->pin, OUTPUT);
	analogWrite(this->pin, 0);
	return ERR_OK;
}

void MP_LED_AH::update(unsigned long current_time) 
{

}

void MP_LED_AH::printStatus() 
{
	Serial.print(F("brightness = "));
	Serial.print(this->brightness);
}

void MP_LED_AH::on(int brightness)
{
	this->brightness = brightness;
	analogWrite(this->pin, map(brightness, 0, 100, 0, 255));
}

void MP_LED_AH::off()
{
	this->brightness = 0;
	// digitalWrite and analogWrite don't mix well in ESP32 so we use analogWrite with duty cycle = 0% instead
	analogWrite(this->pin, 0);
}