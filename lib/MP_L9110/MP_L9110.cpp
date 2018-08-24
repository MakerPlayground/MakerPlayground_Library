#include "MP_L9110.h"

MP_L9110::MP_L9110(uint8_t inA, uint8_t inB, const String &tag)
	:inA(inA)
	,inB(inB)
	,tag(tag)
{
}

void MP_L9110::init()
{
	pinMode(inA, OUTPUT);
	pinMode(inB, OUTPUT);
	digitalWrite(inA, LOW);
	digitalWrite(inB, LOW);
}

void MP_L9110::on(char dir[], int speed)
{
	speed = map(speed, 0, 100, 0, 255);
	if (strcmp(dir, "Forward") == 0)
	{
		analogWrite(inA, speed);
		digitalWrite(inB, LOW);
	}
	else
	{
		digitalWrite(inA, LOW);
		analogWrite(inB, speed);
	}
}

void MP_L9110::off()
{
	digitalWrite(inA, LOW);
	digitalWrite(inB, LOW);
}
