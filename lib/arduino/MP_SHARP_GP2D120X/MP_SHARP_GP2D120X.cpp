#include "MP_SHARP_GP2D120X.h"

MP_SHARP_GP2D120X::MP_SHARP_GP2D120X(uint8_t pin)
  : pin(pin)
{
}

int MP_SHARP_GP2D120X::init()  
{	
    return ERR_OK;
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
