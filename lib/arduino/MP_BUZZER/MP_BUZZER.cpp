#include "MP_BUZZER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BUZZER::ERRORS = errors_p;

MP_BUZZER::MP_BUZZER(uint8_t pin)
	: pin(pin)
	, playing(false)
	, endTime(0)
{
}

int MP_BUZZER::init()
{
	pinMode(this->pin, OUTPUT);
	noTone(this->pin);
	return 0;
}

void MP_BUZZER::update(unsigned long current_time) 
{
	if (playing && (current_time > endTime)) 
	{
		noTone(this->pin);
		playing = false;
	}
}

void MP_BUZZER::printStatus() {
	Serial.print(F("If this device is not work properly, check the connection on pin "));
	Serial.println(this->pin);
}

void MP_BUZZER::beep()
{
	tone(this->pin, 2000);
	endTime = millis() + 100;
	playing = true;
}

void MP_BUZZER::play(double frequency, double duration)
{
	tone(this->pin, frequency);
	endTime = millis() + (duration * 1000);
	playing = true;
}
