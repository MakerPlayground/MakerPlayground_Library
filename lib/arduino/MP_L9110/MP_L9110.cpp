#include "MP_L9110.h"

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
	return ERR_OK;
}

void MP_L9110::update(unsigned long current_time)
{

}

void MP_L9110::printStatus()
{
	Serial.print("Motor is now ");
	Serial.println(status);
}

void MP_L9110::on(uint8_t dir, int speed)
{
	speed = map(speed, 0, 100, 0, 255);
	// Forward - 1, Backward - 0
	if (dir == 1)
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
