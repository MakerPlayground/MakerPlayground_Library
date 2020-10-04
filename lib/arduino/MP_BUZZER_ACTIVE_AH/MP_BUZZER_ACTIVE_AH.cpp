#include "MP_BUZZER_ACTIVE_AH.h"

MP_BUZZER_ACTIVE_AH::MP_BUZZER_ACTIVE_AH(uint8_t pin)
	: pin(pin)
	, playing(false)
	, endTime(0)
{
}

int MP_BUZZER_ACTIVE_AH::init()
{
	return MP_ERR_OK;
}

void MP_BUZZER_ACTIVE_AH::update(unsigned long current_time) 
{
	if (playing && (current_time > endTime)) 
	{
		digitalWrite(this->pin, LOW);
		playing = false;
	}
}

void MP_BUZZER_ACTIVE_AH::printStatus() {
	Serial.print(F("If this device is not work properly, check the connection on pin "));
	Serial.println(this->pin);
}

void MP_BUZZER_ACTIVE_AH::beep()
{
	digitalWrite(this->pin, HIGH);
	endTime = millis() + 100;
	playing = true;
}

void MP_BUZZER_ACTIVE_AH::play(double frequency, double duration)
{
	digitalWrite(this->pin, HIGH);
	endTime = millis() + (duration * 1000);
	playing = true;
}
