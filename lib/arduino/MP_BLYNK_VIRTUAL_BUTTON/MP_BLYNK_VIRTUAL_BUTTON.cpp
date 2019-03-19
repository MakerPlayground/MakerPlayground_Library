#include "MP_BLYNK_VIRTUAL_BUTTON.h"

MP_BLYNK_VIRTUAL_BUTTON::MP_BLYNK_VIRTUAL_BUTTON(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_BUTTON::init() {
    if (!blynk)
        return ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return ERR_CLIENT_NOT_READY;
    return ERR_OK;
}

void MP_BLYNK_VIRTUAL_BUTTON::printStatus() {
    Serial.print(F("Button is now "));
    Serial.println(bPress ? "pressed" : "released");
}

void MP_BLYNK_VIRTUAL_BUTTON::update(unsigned long current_time) {
    bPress = blynk->readVirtualPin(v_pin);
}

bool MP_BLYNK_VIRTUAL_BUTTON::isPress() {
    return bPress;
}

bool MP_BLYNK_VIRTUAL_BUTTON::isPressAndRelease(){
    if(bPress)
    {
        while (bPress) {
            blynk->update(millis());
            update(millis());
        }
        return true;
    }
    return false;
}

bool MP_BLYNK_VIRTUAL_BUTTON::isNotPress(){
    return !bPress;
}