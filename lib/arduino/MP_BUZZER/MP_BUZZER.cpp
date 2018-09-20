#include "MP_BUZZER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BUZZER::ERRORS = errors_p;

MP_BUZZER::MP_BUZZER(uint8_t pin)
	:pin(pin)
{
}

int MP_BUZZER::init()
{
	pinMode(this->pin, OUTPUT);
	return 0;
}

void MP_BUZZER::update(unsigned long current_time) 
{
	
}

void MP_BUZZER::printStatus() {
	Serial.print(F("If this device is not work properly, check the connection on pin "));
	Serial.println(this->pin);
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
