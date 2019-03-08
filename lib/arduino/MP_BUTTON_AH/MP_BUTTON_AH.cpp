#include "MP_BUTTON_AH.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BUTTON_AH::ERRORS = errors_p;

MP_BUTTON_AH::MP_BUTTON_AH(uint8_t pin)
	:pin(pin)
{
}

int MP_BUTTON_AH::init()
{
	pinMode(pin, INPUT_PULLUP);
    checkpoint = millis();
	return 0;
}

void MP_BUTTON_AH::update(unsigned long current_time)
{
    if (state == NOTHING && isPress() && current_time - checkpoint >= 30) {
        state = PRESSED;
    }
    if (state == PRESSED && isNotPress()) {
        state = JUST_RELEASE;
        checkpoint = millis();
    }
    if (state == JUST_RELEASE && current_time - checkpoint >= 150) {
        state = NOTHING;
    }
}

void MP_BUTTON_AH::printStatus() 
{
	Serial.print(F("Button is "));
	Serial.println(isPress() ? F("pressed"): F("not pressed"));
}

bool MP_BUTTON_AH::isPress()
{
    return (digitalRead(pin) == HIGH);
}

bool MP_BUTTON_AH::isPressAndRelease()
{
    if (state == JUST_RELEASE) {
        state = NOTHING;
        checkpoint = millis();
        return true;
    }
    return false;
}

bool MP_BUTTON_AH::isNotPress()
{
    return (digitalRead(pin) == LOW);
}