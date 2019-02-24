#include "MP_L9110.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_L9110::ERRORS = errors_p;

MP_L9110::MP_L9110(uint8_t inA, uint8_t inB)
	:inA(inA)
	,inB(inB)
	,status("")
{
}

int MP_L9110::init()
{
	pinMode(inA, OUTPUT);
	pinMode(inB, OUTPUT);
	digitalWrite(inA, LOW);
	digitalWrite(inB, LOW);
	return 0;
}

void MP_L9110::update(unsigned long current_time)
{

}

void MP_L9110::printStatus()
{
	Serial.print("Motor is now ");
	Serial.println(status);
}

void MP_L9110::on(char dir[], int speed)
{
	speed = map(speed, 0, 100, 0, 255);
	if (strcmp(dir, "Forward") == 0)
	{
		analogWrite(inA, speed);
		digitalWrite(inB, LOW);
		status = "forward";
	}
	else
	{
		digitalWrite(inA, LOW);
		analogWrite(inB, speed);
		status = "backward";
	}
}

void MP_L9110::off()
{
	digitalWrite(inA, LOW);
	digitalWrite(inB, LOW);
	status = "off";
}
