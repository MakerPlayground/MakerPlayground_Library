#include "MP_PAM8302.h"

MP_PAM8302::MP_PAM8302(uint8_t speakerPin)
	:speakerPin(speakerPin)
{
}

void MP_PAM8302::init()
{
	pinMode(speakerPin, OUTPUT);
}

void MP_PAM8302::beep(float percentage, uint16_t dur)
{
	analogWrite(speakerPin, 255*(percentage/100.0));
	delay(dur);
}

void MP_PAM8302::tone(uint16_t hz, uint16_t dur)
{
	tone(speakerPin, hz);
	delay(dur);
}
