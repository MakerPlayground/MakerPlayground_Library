#include "MP_PIR.h"

MP_PIR::MP_PIR(uint8_t pin)
	:pin(pin)
{
}

int MP_PIR::init()
{
	isMotionDetected = false;
	pinMode(this->pin, INPUT);
	return MP_ERR_OK;
}

void MP_PIR::update(unsigned long current_time)
{
	this->isMotionDetected = (digitalRead(pin) == HIGH);
}

void MP_PIR::printStatus()
{
	Serial.print(F("Motion is "));
	Serial.println(this->isMotionDetected ? "detected": "not detected");
}

bool MP_PIR::isDetected()
{
	return this->isMotionDetected;
}

bool MP_PIR::isNotDetected()
{
	return !(this->isMotionDetected);
}
