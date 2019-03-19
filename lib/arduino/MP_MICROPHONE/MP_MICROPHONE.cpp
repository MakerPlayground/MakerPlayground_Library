#include "MP_MICROPHONE.h"

MP_MICROPHONE::MP_MICROPHONE(uint8_t pin)
	:pin(pin)
{
}

int MP_MICROPHONE::init()
{
	this->soundLevel = 0;
	pinMode(pin, INPUT);
	return ERR_OK;
}

void MP_MICROPHONE::update(unsigned long current_time)
{
	this->soundLevel = 100.0*analogRead(pin)/1023.0;
}

void MP_MICROPHONE::printStatus()
{
	Serial.print(F("sound level = "));
	Serial.println(this->soundLevel);
}

double MP_MICROPHONE::getSoundLevel()
{
	return this->soundLevel;
}
