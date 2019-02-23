#include "MP_SHARP_GP2D120X.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_SHARP_GP2D120X::ERRORS = errors_p;

MP_SHARP_GP2D120X::MP_SHARP_GP2D120X(uint8_t pin)
  : pin(pin)
{
}

int MP_SHARP_GP2D120X::init()  
{	
    return 0;
}

void MP_SHARP_GP2D120X::update(unsigned long current_time)
{
    int value = analogRead(18);
    cm = 2076.0 / ((value < 16 ? 16 : value) - 11.0);
    if(cm < 4) cm = 4;
    if(cm > 30) cm = 30;
}

void MP_SHARP_GP2D120X::printStatus()
{
    Serial.print(F("distance (cm.) = "));
    Serial.println(this->cm);
}

double MP_SHARP_GP2D120X::getDistance() 
{
    return cm;
}
