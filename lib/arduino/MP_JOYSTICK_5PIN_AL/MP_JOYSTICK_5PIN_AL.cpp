#include "MP_JOYSTICK_5PIN_AL.h"

MP_JOYSTICK_5PIN_AL::MP_JOYSTICK_5PIN_AL(uint8_t upPin, uint8_t leftPin, uint8_t rightPin, uint8_t pressPin, uint8_t downPin)
	: upPin(upPin)
    , leftPin(leftPin)
    , rightPin(rightPin)
    , pressPin(pressPin)
    , downPin(downPin)
{
}

int MP_JOYSTICK_5PIN_AL::init()
{
	pinMode(upPin, INPUT_PULLUP);
	pinMode(leftPin, INPUT_PULLUP);
	pinMode(rightPin, INPUT_PULLUP);
	pinMode(pressPin, INPUT_PULLUP);
	pinMode(downPin, INPUT_PULLUP);
	return MP_ERR_OK;
}

void MP_JOYSTICK_5PIN_AL::update(unsigned long current_time)
{
}

void MP_JOYSTICK_5PIN_AL::printStatus() 
{
	Serial.print(F("Button is "));
	Serial.println((digitalRead(pin) == LOW) ? F("pressed"): F("not pressed"));
}

bool MP_JOYSTICK_5PIN_AL::isUpPress() {
    return digitalRead(upPin) == LOW;
}

bool MP_JOYSTICK_5PIN_AL::isDownPress() {
    return digitalRead(downPin) == LOW;
}

bool MP_JOYSTICK_5PIN_AL::isLeftPress() {
    return digitalRead(leftPin) == LOW;
}

bool MP_JOYSTICK_5PIN_AL::isRightPress() {
    return digitalRead(rightPin) == LOW;
}

bool MP_JOYSTICK_5PIN_AL::isMiddlePress() {
    return digitalRead(pressPin) == LOW;
}

bool MP_JOYSTICK_5PIN_AL::isUpRelease() {
    return digitalRead(upPin) == HIGH;
}

bool MP_JOYSTICK_5PIN_AL::isDownRelease() {
    return digitalRead(downPin) == HIGH;
}

bool MP_JOYSTICK_5PIN_AL::isLeftRelease() {
    return digitalRead(leftPin) == HIGH;
}

bool MP_JOYSTICK_5PIN_AL::isRightRelease() {
    return digitalRead(rightPin) == HIGH;
}

bool MP_JOYSTICK_5PIN_AL::isMiddleRelease() {
    return digitalRead(pressPin) == HIGH;
}

bool MP_JOYSTICK_5PIN_AL::isAllRelease() {
    return (digitalRead(upPin) == HIGH)
        && (digitalRead(leftPin) == HIGH)
        && (digitalRead(rightPin) == HIGH)
        && (digitalRead(pressPin) == HIGH)
        && (digitalRead(downPin) == HIGH);
}