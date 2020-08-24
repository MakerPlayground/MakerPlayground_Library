#include "MP_NETPIE_VIRTUAL_BUTTON.h"

MP_NETPIE_VIRTUAL_BUTTON::MP_NETPIE_VIRTUAL_BUTTON(char* topic, MP_NETPIE* netpie)
    : topic(topic)
    , netpie(netpie)
{
}

int MP_NETPIE_VIRTUAL_BUTTON::init()
{
    netpie->subscribe(topic);
    checkpoint = millis();
    return MP_ERR_OK;
}
    
void MP_NETPIE_VIRTUAL_BUTTON::printStatus()
{
    Serial.print(F("Virtual button is now "));
    Serial.println(bPress ? "pressed": "not pressed");
}

void MP_NETPIE_VIRTUAL_BUTTON::update(unsigned long current_time)
{
    bPress = (netpie->getValue(topic) != 0);
    if (state == NOTHING && bPress && current_time >= 30 + checkpoint) {
        state = PRESSED;
    }
    if (state == PRESSED && !bPress) {
        state = JUST_RELEASE;
        checkpoint = millis();
    }
    if (state == JUST_RELEASE && current_time >= 150 + checkpoint) {
        state = NOTHING;
    }
}

bool MP_NETPIE_VIRTUAL_BUTTON::isPress() {
    return bPress;
}

bool MP_NETPIE_VIRTUAL_BUTTON::isPressAndRelease()
{
    return state == JUST_RELEASE;
}

bool MP_NETPIE_VIRTUAL_BUTTON::isNotPress(){
    return !bPress;
}