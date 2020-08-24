#include "MP_BLYNK_VIRTUAL_BUTTON.h"

MP_BLYNK_VIRTUAL_BUTTON::MP_BLYNK_VIRTUAL_BUTTON(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_BUTTON::init() {
    if (!blynk)
        return MP_ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return MP_ERR_CLIENT_NOT_READY;
    checkpoint = millis();
    return MP_ERR_OK;
}

void MP_BLYNK_VIRTUAL_BUTTON::printStatus() {
    Serial.print(F("Virtual button is now "));
    Serial.println(bPress ? "pressed" : "released");
}

void MP_BLYNK_VIRTUAL_BUTTON::update(unsigned long current_time) {
    bPress = blynk->readVirtualPin(v_pin);
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

bool MP_BLYNK_VIRTUAL_BUTTON::isPress() {
    return bPress;
}

bool MP_BLYNK_VIRTUAL_BUTTON::isPressAndRelease(){
    return state == JUST_RELEASE;
}

bool MP_BLYNK_VIRTUAL_BUTTON::isNotPress(){
    return !bPress;
}