#include "MP_NETPIE_VIRTUAL_BUTTON.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE_VIRTUAL_BUTTON::ERRORS = errors_p;

MP_NETPIE_VIRTUAL_BUTTON::MP_NETPIE_VIRTUAL_BUTTON(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_BUTTON::init()
{
    (netpie->getMicrogear()).subscribe(topic);
    return 0;
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

bool MP_NETPIE_VIRTUAL_BUTTON::isPressAndRelease(){
    if(bPress)
    {
        while (bPress) {
            if ((netpie->getMicrogear()).connected())
            {
                // this method need to be called regularly to avoid connection lost
                (netpie->getMicrogear()).loop();
            }
            update(millis());
        }
        return true;
    }
    return false;
}

bool MP_NETPIE_VIRTUAL_BUTTON::isNotPress(){
    return !bPress;
}