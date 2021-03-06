#include "VD_TIMER.h"

VD_TIMER::VD_TIMER()
{
}

int VD_TIMER::init() 
{
    this->isStarted = false;
    this->second = 0;
    return MP_ERR_OK;
}

void VD_TIMER::update(unsigned long current_time) 
{
    this->second = !this->isStarted ? 0 : (current_time - start) / 1000;
}

void VD_TIMER::printStatus()
{
    Serial.print(F("second = "));
    Serial.println(this->second);
}

int VD_TIMER::getSecond()
{
    return this->second;
}

void VD_TIMER::startTimer()
{
    this->isStarted = true;
    this->start = millis();
}

bool VD_TIMER::isOverTime(int second)
{
    return isStarted && this->second >= second;
}

bool VD_TIMER::isNotOverTime(int second)
{
    return isStarted && this->second < second;
}

void VD_TIMER::stopTimer()
{
    this->isStarted = false;
    this->second = 0;
}
