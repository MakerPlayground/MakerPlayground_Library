#include "MP_GROVE_ULTRASONIC_RANGER.h"

#define READ_INTERVAL 50 // ms

MP_GROVE_ULTRASONIC_RANGER::MP_GROVE_ULTRASONIC_RANGER(uint8_t pin)
  : pin(pin)
  , latestReadTime(0)
{

}

int MP_GROVE_ULTRASONIC_RANGER::init()
{
	this->cm = 0;
	pinMode(this->pin,INPUT);
	return MP_ERR_OK;
}

void MP_GROVE_ULTRASONIC_RANGER::update(unsigned long current_time)
{
	if (current_time - latestReadTime > READ_INTERVAL)
	{
		pinMode(this->pin, OUTPUT);
		digitalWrite(this->pin, LOW);
		delayMicroseconds(2);
		digitalWrite(this->pin, HIGH);
		delayMicroseconds(5);
		digitalWrite(this->pin,LOW);
		pinMode(this->pin,INPUT);
		long duration = pulseIn(this->pin,HIGH);
		this->cm = duration / 58.0;
		latestReadTime = current_time;
	}
}

void MP_GROVE_ULTRASONIC_RANGER::printStatus()
{
	Serial.print(F("distance (cm.) = "));
	Serial.println(this->cm);
}

double MP_GROVE_ULTRASONIC_RANGER::getDistance()
{
    return this->cm;
}
