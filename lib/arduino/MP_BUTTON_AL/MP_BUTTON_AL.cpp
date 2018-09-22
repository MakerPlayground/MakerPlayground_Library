#include "MP_BUTTON_AL.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BUTTON_AL::ERRORS = errors_p;

MP_BUTTON_AL::MP_BUTTON_AL(uint8_t pin)
	:pin(pin)
{
}

int MP_BUTTON_AL::init()
{
	pinMode(pin, INPUT_PULLUP);
	return 0;
}

void MP_BUTTON_AL::update(unsigned long current_time)
{

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
    if(digitalRead(pin) == LOW)
    {
        delay(30);  // debounce
        while (digitalRead(pin) == LOW);
        delay(30);  // debounce
        return true;
    }
    return false;
}

bool MP_BUTTON_AL::isNotPress()
{
    return (digitalRead(pin) == HIGH);
}