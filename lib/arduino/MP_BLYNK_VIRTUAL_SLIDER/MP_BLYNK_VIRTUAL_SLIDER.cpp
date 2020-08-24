#include "MP_BLYNK_VIRTUAL_SLIDER.h"

MP_BLYNK_VIRTUAL_SLIDER::MP_BLYNK_VIRTUAL_SLIDER(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_SLIDER::init() {
    if (!blynk)
        return MP_ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return MP_ERR_CLIENT_NOT_READY;
    return MP_ERR_OK;
}

void MP_BLYNK_VIRTUAL_SLIDER::printStatus() {
    Serial.print(F("Current value = "));
    Serial.println(value);
}

void MP_BLYNK_VIRTUAL_SLIDER::update(unsigned long current_time) {
    value = blynk->readVirtualPin(v_pin);
}

double MP_BLYNK_VIRTUAL_SLIDER::getValue() {
    return value;
}