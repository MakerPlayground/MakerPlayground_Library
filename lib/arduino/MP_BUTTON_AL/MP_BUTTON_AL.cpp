#include "MP_BUTTON_AL.h"

MP_BUTTON_AL::MP_BUTTON_AL(uint8_t pin)
	:pin(pin)
{
}

int MP_BUTTON_AL::init()
{
	pinMode(pin, INPUT_PULLUP);
    checkpoint = millis();
	return MP_ERR_OK;
}

void MP_BUTTON_AL::update(unsigned long current_time)
{
    if (state == NOTHING && isPress() && current_time >= 30 + checkpoint) {
        state = PRESSED;
    }
    if (state == PRESSED && isNotPress()) {
        state = JUST_RELEASE;
        checkpoint = millis();
    }
    if (state == JUST_RELEASE && current_time >= 150 + checkpoint) {
        state = NOTHING;
    }
}

void MP_BUTTON_AL::printStatus() 
{
	Serial.print(F("Button is "));
	Serial.println((digitalRead(pin) == LOW) ? F("pressed"): F("not pressed"));
}

bool MP_BUTTON_AL::isPress()
{
    return (digitalRead(pin) == LOW);
}

bool MP_BUTTON_AL::isPressAndRelease()
{
    return state == JUST_RELEASE;
}

bool MP_BUTTON_AL::isNotPress()
{
    return (digitalRead(pin) == HIGH);
}