#include "MP_BLYNK_VIRTUAL_BUTTON.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "no Blynk object";
const char error2[] PROGMEM = "Blynk is not ready";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK_VIRTUAL_BUTTON::ERRORS = errors_p;

MP_BLYNK_VIRTUAL_BUTTON::MP_BLYNK_VIRTUAL_BUTTON(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_BUTTON::init() {
    if (!blynk)
        return 1;
    if (!blynk->isReady())
        return 2;
    return 0;
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