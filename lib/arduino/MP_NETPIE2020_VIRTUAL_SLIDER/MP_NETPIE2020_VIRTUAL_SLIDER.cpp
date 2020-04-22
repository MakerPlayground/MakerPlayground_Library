#include "MP_NETPIE2020_VIRTUAL_SLIDER.h"

MP_NETPIE2020_VIRTUAL_SLIDER::MP_NETPIE2020_VIRTUAL_SLIDER(char* topic, MP_NETPIE2020* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE2020_VIRTUAL_SLIDER::init()
{
    netpie->subscribe(topic);
    return ERR_OK;
}
    
void MP_NETPIE2020_VIRTUAL_SLIDER::printStatus()
{
    Serial.print(F("Current value = "));
    Serial.println(value);
}

void MP_NETPIE2020_VIRTUAL_SLIDER::update(unsigned long time)
{
    value = netpie->getValue(topic);
}

double MP_NETPIE2020_VIRTUAL_SLIDER::getValue() {
    return value;
}