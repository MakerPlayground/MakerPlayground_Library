#include "MP_BUTTON_AH.h"

MP_BUTTON_AH::MP_BUTTON_AH(uint8_t pin)
	:pin(pin)
{
}

int MP_BUTTON_AH::init()
{
	pinMode(pin, INPUT);
    checkpoint = millis();
	return MP_ERR_OK;
}

void MP_BUTTON_AH::update(unsigned long current_time)
{
    if (state == RELEASED && (digitalRead(pin) == HIGH) && current_time >= 30 + checkpoint) {
        state = PRESSED;
        checkpoint = millis();
    }
    else if (state == PRESSED && (digitalRead(pin) == LOW) && current_time >= 30 + checkpoint) {
        state = JUST_RELEASE;
        checkpoint = millis();
    }
    else if (state == JUST_RELEASE && current_time >= 150 + checkpoint) {
        state = RELEASED;
        checkpoint = millis();
    }
}

void MP_BUTTON_AH::printStatus() 
{
	Serial.print(F("Button is "));
	Serial.println(isPress() ? F("pressed"): F("not pressed"));
}

bool MP_BUTTON_AH::isPress()
{
    return state == PRESSED; // (digitalRead(pin) == HIGH);
}

bool MP_BUTTON_AH::isPressAndRelease()
{
    if (state == JUST_RELEASE) {
        state = RELEASED;
        checkpoint = millis();
        return true;
    }
    return false;
}

bool MP_BUTTON_AH::isNotPress()
{
    return state == RELEASED; // (digitalRead(pin) == LOW);
}