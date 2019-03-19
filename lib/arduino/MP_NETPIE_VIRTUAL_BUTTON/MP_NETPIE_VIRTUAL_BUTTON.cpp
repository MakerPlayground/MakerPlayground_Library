#include "MP_NETPIE_VIRTUAL_BUTTON.h"

MP_NETPIE_VIRTUAL_BUTTON::MP_NETPIE_VIRTUAL_BUTTON(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_BUTTON::init()
{
    netpie->subscribe(topic);
    return ERR_OK;
}
    
void MP_NETPIE_VIRTUAL_BUTTON::printStatus()
{
    Serial.print(F("Button is "));
    Serial.println(bPress ? "pressed": "not pressed");
}

void MP_NETPIE_VIRTUAL_BUTTON::update(unsigned long time)
{
    bPress = (netpie->getValue(topic) != 0);
}

bool MP_NETPIE_VIRTUAL_BUTTON::isPress() {
    return bPress;
}

bool MP_NETPIE_VIRTUAL_BUTTON::isPressAndRelease()
{
    if(bPress)
    {
        while (bPress)
        {
            netpie->update(millis());
            update(millis());
        }
        return true;
    }
    return false;
}

bool MP_NETPIE_VIRTUAL_BUTTON::isNotPress(){
    return !bPress;
}