#include "MP_HC_SR04.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_HC_SR04::ERRORS = errors_p;

MP_HC_SR04::MP_HC_SR04(uint8_t trig, uint8_t echo)
  : trig(trig), echo(echo), cm(0), nextReading(0)
{
}

int MP_HC_SR04::init()  
{	
	pinMode(this->trig, OUTPUT);
	digitalWrite(this->trig, LOW);
	pinMode(this->echo, INPUT);
    return 0;
}

void MP_HC_SR04::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 100;       // next reading should happen at least 36(max echo pulse width)+10(gap according to the datasheet)=46ms
                                                // later otherwise the sound wave from previous reading may interfere with the new reading
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        cm = pulseIn(echo, HIGH, 30000) / 58;   // we need to wait for a few ms before the pulse start and
                                                // a pulse with 26.1uS width is returned for distance of 4.5m
                                                // so we wait for 30ms before timeout and return 0
        if (cm == 0 || cm > 450)
        {
            cm = 450;
        }
    }
}

void MP_HC_SR04::printStatus()
{
    Serial.print(F("distance (cm.) = "));
    Serial.println(this->cm);
}

double MP_HC_SR04::getDistance() 
{
    return cm;
}
