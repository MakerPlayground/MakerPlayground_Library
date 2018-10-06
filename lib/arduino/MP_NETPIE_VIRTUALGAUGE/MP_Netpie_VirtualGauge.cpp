#include "MP_Netpie_VirtualGauge.h"

MP_Netpie_VirtualGauge::MP_Netpie_VirtualGauge(char* topic, MP_Netpie_ESP8266* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_Netpie_VirtualGauge::init()
{
    return 0;
}
    
void MP_Netpie_VirtualGauge::update(unsigned long time)
{
}

void MP_Netpie_VirtualGauge::setNumber(double value)
{
    netpie->publish(topic, value);
}