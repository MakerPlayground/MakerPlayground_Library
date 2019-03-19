#include "MP_BLYNK_VIRTUAL_SLIDER.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "no Blynk object";
const char error2[] PROGMEM = "Blynk is not ready";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK_VIRTUAL_SLIDER::ERRORS = errors_p;

MP_BLYNK_VIRTUAL_SLIDER::MP_BLYNK_VIRTUAL_SLIDER(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_SLIDER::init() {
    if (!blynk)
        return ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return ERR_CLIENT_NOT_READY;
    return ERR_OK;
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