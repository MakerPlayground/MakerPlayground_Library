#include "MP_IR_REFLECTOR.h"

MP_IR_REFLECTOR::MP_IR_REFLECTOR(uint8_t pin)
	:pin(pin)
{
}

int MP_IR_REFLECTOR::init()
{
	pinMode(this->pin, INPUT);
	return ERR_OK;
}

bool MP_IR_REFLECTOR::isDetected()
{
	return isDetected;
}

bool MP_IR_REFLECTOR::isNotDetected()
{
	return !isDetected;
}

void MP_IR_REFLECTOR::update(unsigned long current_time)
{
    isDetected = (digitalRead(pin) == LOW);
}

void MP_IR_REFLECTOR::printStatus()
{
    Serial.print(F("Obstrucle is "));
    Serial.println(isDetected ? "detected" : "not detected");
}
