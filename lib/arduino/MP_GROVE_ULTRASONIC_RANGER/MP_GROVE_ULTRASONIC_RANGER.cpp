#include "MP_GROVE_ULTRASONIC_RANGER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_GROVE_ULTRASONIC_RANGER::ERRORS = errors_p;

MP_GROVE_ULTRASONIC_RANGER::MP_GROVE_ULTRASONIC_RANGER(uint8_t pin)
  : pin(pin)
{
  
}

int MP_GROVE_ULTRASONIC_RANGER::init() 
{
	this->cm = 0;
	pinMode(this->pin,INPUT);
	return 0;
}

void MP_GROVE_ULTRASONIC_RANGER::update(unsigned long current_time)
{
	double RangeInCentimeters = 0.0;
	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);
	delayMicroseconds(2);
	digitalWrite(this->pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(this->pin,LOW);
	pinMode(this->pin,INPUT);
	double duration = pulseIn(this->pin,HIGH);
	RangeInCentimeters = duration/29/2;
	this->cm = RangeInCentimeters;
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
