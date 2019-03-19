#include "MP_HC_SR04.h"

MP_HC_SR04::MP_HC_SR04(uint8_t trig, uint8_t echo)
  : trig(trig), echo(echo), cm(0), nextReading(0), sonar(trig, echo, 500)
{
}

int MP_HC_SR04::init()  
{	
    return ERR_OK;
}

void MP_HC_SR04::update(unsigned long current_time)
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;    // next reading should happen at least 36(max echo pulse width)+10(gap according to the datasheet)=46ms
                                            // later otherwise the sound wave from previous reading may interfere with the new reading
        cm = sonar.convert_cm(sonar.ping_median());
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
