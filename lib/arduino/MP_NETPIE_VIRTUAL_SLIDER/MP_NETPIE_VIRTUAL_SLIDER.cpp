#include "MP_NETPIE_VIRTUAL_SLIDER.h"

MP_NETPIE_VIRTUAL_SLIDER::MP_NETPIE_VIRTUAL_SLIDER(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_SLIDER::init()
{
    netpie->subscribe(topic);
    return MP_ERR_OK;
}
    
void MP_NETPIE_VIRTUAL_SLIDER::printStatus()
{
    Serial.print(F("Current value = "));
    Serial.println(value);
}

void MP_NETPIE_VIRTUAL_SLIDER::update(unsigned long time)
{
    value = netpie->getValue(topic);
}

double MP_NETPIE_VIRTUAL_SLIDER::getValue() {
    return value;
}