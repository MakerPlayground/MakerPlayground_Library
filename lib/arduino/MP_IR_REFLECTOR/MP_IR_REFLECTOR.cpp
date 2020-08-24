#include "MP_IR_REFLECTOR.h"

MP_IR_REFLECTOR::MP_IR_REFLECTOR(uint8_t pin)
	:pin(pin)
{
}

int MP_IR_REFLECTOR::init()
{
	pinMode(this->pin, INPUT);
	return MP_ERR_OK;
}

bool MP_IR_REFLECTOR::isDetected()
{
	return detected;
}

bool MP_IR_REFLECTOR::isNotDetected()
{
	return !detected;
}

void MP_IR_REFLECTOR::update(unsigned long current_time)
{
    detected = (digitalRead(pin) == LOW);
}

void MP_IR_REFLECTOR::printStatus()
{
    Serial.print(F("Obstrucle is "));
    Serial.println(detected ? "detected" : "not detected");
}
