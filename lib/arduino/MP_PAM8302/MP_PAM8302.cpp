#include "MP_PAM8302.h"

MP_PAM8302::MP_PAM8302(uint8_t speakerPin)
	:speakerPin(speakerPin)
{
}

int MP_PAM8302::init()
{
	pinMode(speakerPin, OUTPUT);
	return MP_ERR_OK;
}

void MP_PAM8302::update(unsigned long current_time)
{

}

void MP_PAM8302::printStatus()
{
	Serial.println("-");
}

void MP_PAM8302::beep(float percentage, uint16_t dur)
{
	analogWrite(speakerPin, 255*(percentage/100.0));
	delay(dur);
	analogWrite(speakerPin, 0);
}

void MP_PAM8302::tone(uint16_t hz, uint16_t dur)
{
	tone(speakerPin, hz);
	delay(dur);
}
