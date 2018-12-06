#include "MP_NETPIE_VIRTUAL_SLIDER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE_VIRTUAL_SLIDER::ERRORS = errors_p;

MP_NETPIE_VIRTUAL_SLIDER::MP_NETPIE_VIRTUAL_SLIDER(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_SLIDER::init()
{
    (netpie->getMicrogear()).subscribe(topic);
    return 0;
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