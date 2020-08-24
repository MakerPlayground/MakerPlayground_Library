#include "MP_NTC_NCP_WF.h"

MP_NTC_NCP_WF::MP_NTC_NCP_WF(uint8_t pin)
  : pin(pin)
{
  
}

int MP_NTC_NCP_WF::init() 
{
    this->celcius = 25;
	pinMode(this->pin, INPUT);
    return MP_ERR_OK;
}

void MP_NTC_NCP_WF::update(unsigned long current_time)
{
    this->celcius = 1.0/(log(1023.0/analogRead(this->pin)-1.0)/B+1/298.15)-273.15; 
    // more info: http://www.mwftr.com/emblab/Temp%20Sensor%20-NCP18WF104F03RC.pdf
}

void MP_NTC_NCP_WF::printStatus()
{
    Serial.print(F("temperature (C) = "));
    Serial.println(this->celcius);
}

double MP_NTC_NCP_WF::getTemperature() 
{
    return this->celcius;
}
