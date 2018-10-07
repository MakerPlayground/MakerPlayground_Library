#include "MP_NETPIE_VIRTUAL_LED.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE_VIRTUAL_LED::ERRORS = errors_p;

MP_NETPIE_VIRTUAL_LED::MP_NETPIE_VIRTUAL_LED(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_LED::init()
{
    return 0;
}
    
void MP_NETPIE_VIRTUAL_LED::update(unsigned long time)
{
}

void MP_NETPIE_VIRTUAL_LED::printStatus()
{
    Serial.print(F("LED is now "));
    serial.println(ledStatus ? "on": "off");
}

void MP_NETPIE_VIRTUAL_LED::on()
{
    ledStatus = true;
    netpie->publish(topic, 1);
}

void MP_NETPIE_VIRTUAL_LED::off()
{
    ledStatus = false;
    netpie->publish(topic, 0);
}