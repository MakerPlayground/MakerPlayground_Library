#include "MP_JOYSTICK_LCR.h"

MP_JOYSTICK_LCR::MP_JOYSTICK_LCR(uint8_t leftPin, uint8_t middlePin, uint8_t rightPin)
	: leftPin(leftPin)
	, middlePin(middlePin)
    , rightPin(rightPin)
{
}

int MP_JOYSTICK_LCR::init()
{
	pinMode(leftPin, INPUT_PULLUP);
	pinMode(middlePin, INPUT_PULLUP);
	pinMode(rightPin, INPUT_PULLUP);
	return MP_ERR_OK;
}

void MP_JOYSTICK_LCR::update(unsigned long current_time)
{
}

void MP_JOYSTICK_LCR::printStatus() 
{
}

bool MP_JOYSTICK_LCR::isLeftPress() {
    return digitalRead(leftPin) == LOW;
}

bool MP_JOYSTICK_LCR::isRightPress() {
    return digitalRead(rightPin) == LOW;
}

bool MP_JOYSTICK_LCR::isMiddlePress() {
    return digitalRead(middlePin) == LOW;
}

bool MP_JOYSTICK_LCR::isLeftRelease() {
    return digitalRead(leftPin) == HIGH;
}

bool MP_JOYSTICK_LCR::isRightRelease() {
    return digitalRead(rightPin) == HIGH;
}

bool MP_JOYSTICK_LCR::isMiddleRelease() {
    return digitalRead(middlePin) == HIGH;
}

bool MP_JOYSTICK_LCR::isAllRelease() {
    return (digitalRead(leftPin) == HIGH)
        && (digitalRead(rightPin) == HIGH)
        && (digitalRead(middlePin) == HIGH);
}