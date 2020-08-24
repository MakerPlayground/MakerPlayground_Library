#include "MP_NETPIE_VIRTUAL_GAUGE.h"

MP_NETPIE_VIRTUAL_GAUGE::MP_NETPIE_VIRTUAL_GAUGE(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_GAUGE::init()
{
    return MP_ERR_OK;
}
    
void MP_NETPIE_VIRTUAL_GAUGE::printStatus()
{
    Serial.print(F("gauge value = "));
    Serial.println(current_value);
}

void MP_NETPIE_VIRTUAL_GAUGE::update(unsigned long time)
{
}

void MP_NETPIE_VIRTUAL_GAUGE::setNumber(double value)
{
    current_value = value;
    netpie->publish(topic, value);
}