#include "MP_NETPIE_VIRTUAL_GAUGE.h"

MP_NETPIE_VIRTUAL_GAUGE::MP_NETPIE_VIRTUAL_GAUGE(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_GAUGE::init()
{
    return 0;
}
    
void MP_NETPIE_VIRTUAL_GAUGE::update(unsigned long time)
{
}

void MP_NETPIE_VIRTUAL_GAUGE::setNumber(double value)
{
    netpie->publish(topic, value);
}