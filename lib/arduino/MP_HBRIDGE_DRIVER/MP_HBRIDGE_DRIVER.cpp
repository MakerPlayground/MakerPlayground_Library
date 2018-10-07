#include "MP_HBRIDGE_DRIVER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_HBRIDGE_DRIVER::ERRORS = errors_p;

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
	return 0;
}

void MP_HBRIDGE_DRIVER::update(unsigned long current_time) 
{
}

void MP_HBRIDGE_DRIVER::printStatus() {
	Serial.print(F("N/A"));
}

void MP_HBRIDGE_DRIVER::on(char dir[], int speed)
{
	speed = map(speed, 0, 100, 0, 255);
	if (strcmp(dir, "Forward") == 0)
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
