#include "MP_HY_SRF05.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_HY_SRF05::ERRORS = errors_p;

MP_HY_SRF05::MP_HY_SRF05(uint8_t echo, uint8_t trig)
  : trig(trig), echo(echo)
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
    /* loop for filter an hardware error */
    do {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        cm = pulseIn(echo, HIGH) / 29.0 / 2.0 ;
  	} while(cm>3000);
}

void MP_HY_SRF05::printStatus()
{
    Serial.print(F("distance = "));
    Serial.println(this->cm);
}

double MP_HY_SRF05::getDistance() 
{
    return cm;
}
