#include "MP_HBRIDGE_DRIVER.h"

MP_HBRIDGE_DRIVER::MP_HBRIDGE_DRIVER(uint8_t inA, uint8_t inB)
	: inA(inA)
	, inB(inB)
{
}

int MP_HBRIDGE_DRIVER::init()
{
	pinMode(inA, OUTPUT);
	digitalWrite(inA, LOW);
	pinMode(inB, OUTPUT);
	digitalWrite(inB, LOW);
	return ERR_OK;
}

void MP_HBRIDGE_DRIVER::update(unsigned long current_time) 
{
}

void MP_HBRIDGE_DRIVER::printStatus() {
	Serial.print(F("N/A"));
}

void MP_HBRIDGE_DRIVER::on(uint8_t dir, int speed)
{
	speed = map(speed, 0, 100, 0, 255);
	// Forward - 1, Backward - 0
	if (dir == 1)
	{
		analogWrite(inA, speed);
		analogWrite(inB, 0);
	}
	else
	{
		analogWrite(inA, 0);
		analogWrite(inB, speed);
	}
}

void MP_HBRIDGE_DRIVER::off()
{
	analogWrite(inA, 0);
	analogWrite(inB, 0);
}
