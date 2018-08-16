#include "MP_BUZZER.h"

MP_BUZZER::MP_BUZZER(uint8_t pin, const String &tag)
	:pin(pin)
	,tag(tag)
{
}

void MP_BUZZER::init()
{
	pinMode(this->pin, OUTPUT);
}

void MP_BUZZER::beep()
{
	tone(this->pin, 2000);
	delay(100);
	noTone(this->pin);
}

void MP_BUZZER::play(double frequency, double duration)
{
	tone(this->pin, frequency);
	delay(duration*1000);
	noTone(this->pin);
}
