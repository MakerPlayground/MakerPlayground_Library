#include "MP_BLYNK_VIRTUAL_GAUGE.h"

MP_BLYNK_VIRTUAL_GAUGE::MP_BLYNK_VIRTUAL_GAUGE(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_GAUGE::init() {
    if (!blynk)
        return ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return ERR_CLIENT_NOT_READY;
    return ERR_OK;
}

void MP_BLYNK_VIRTUAL_GAUGE::printStatus() {
    Serial.print(F("Current value = "));
    Serial.println(val);
}

void MP_BLYNK_VIRTUAL_GAUGE::update(unsigned long current_time) {
    blynk->update(millis());
}

void MP_BLYNK_VIRTUAL_GAUGE::setNumber(double value) {
    val = value;
    blynk->writeVirtualPin(v_pin, val);
}