#include "MP_NETPIE2020_VIRTUAL_LED.h"

MP_NETPIE2020_VIRTUAL_LED::MP_NETPIE2020_VIRTUAL_LED(char* topic, MP_NETPIE2020* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE2020_VIRTUAL_LED::init()
{
    return ERR_OK;
}
    
void MP_NETPIE2020_VIRTUAL_LED::update(unsigned long time)
{
}

void MP_NETPIE2020_VIRTUAL_LED::printStatus()
{
    Serial.print(F("LED is now "));
    Serial.println(ledStatus ? "on": "off");
}

void MP_NETPIE2020_VIRTUAL_LED::on()
{
    Serial.print("turn on");
    ledStatus = true;
    netpie->publish(topic, 1);
}

void MP_NETPIE2020_VIRTUAL_LED::off()
{
    Serial.print("turn off");
    ledStatus = false;
    netpie->publish(topic, 0);
}