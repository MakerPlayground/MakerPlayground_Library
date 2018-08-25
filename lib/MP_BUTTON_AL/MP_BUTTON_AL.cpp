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
	Serial.print(F("Button is now "));
	Serial.println(digitalRead(pin) == LOW ? "released": "press");
}

boolean MP_BUTTON_AL::isReleased()
{
	if(digitalRead(pin)==LOW)
	{
		delay(30);
		while(digitalRead(pin)==LOW);
		delay(30);
		return true;
	}
	return false;
}

boolean MP_BUTTON_AL::isPressed()
{
	if(digitalRead(pin)==LOW)
	{
		delay(300);
		return true;
	}
	return false;
}