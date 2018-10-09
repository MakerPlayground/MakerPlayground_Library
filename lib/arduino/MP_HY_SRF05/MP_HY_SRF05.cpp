#include "MP_HY_SRF05.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_HY_SRF05::ERRORS = errors_p;

MP_HY_SRF05::MP_HY_SRF05(uint8_t echo, uint8_t trig)
  : trig(trig), echo(echo), cm(0), nextReading(0)
{
}

int MP_HY_SRF05::init()  
{	
	pinMode(this->trig, OUTPUT);
	pinMode(this->echo, INPUT);
    return 0;
}

void MP_HY_SRF05::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;        // next reading should happen at least 50ms later otherwise the sound
                                                // wave from previous reading may interfere with the new reading
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        cm = pulseIn(echo, HIGH, 12000) / 58;   // we need to wait for a few ms before the pulse start and
                                                // a pulse with 8.82uS width is returned for distance of 3m 
                                                // so we wait for 12ms before timeout and return 0
        if (cm == 0 || cm > 300)
        {
            cm = 300;
        }
        Serial.println(cm);
    }
}

void MP_HY_SRF05::printStatus()
{
    Serial.print(F("distance (cm.) = "));
    Serial.println(this->cm);
}

double MP_HY_SRF05::getDistance() 
{
    return cm;
}
