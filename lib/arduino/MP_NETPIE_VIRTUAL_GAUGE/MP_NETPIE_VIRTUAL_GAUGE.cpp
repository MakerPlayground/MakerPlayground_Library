#include "MP_NETPIE_VIRTUAL_GAUGE.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE_VIRTUAL_GAUGE::ERRORS = errors_p;

MP_NETPIE_VIRTUAL_GAUGE::MP_NETPIE_VIRTUAL_GAUGE(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_GAUGE::init()
{
    return 0;
}
    
void MP_NETPIE_VIRTUAL_GAUGE::printStatus()
{
}

void MP_NETPIE_VIRTUAL_GAUGE::update(unsigned long time)
{
}

void MP_NETPIE_VIRTUAL_GAUGE::setNumber(double value)
{
    netpie->publish(topic, value);
}