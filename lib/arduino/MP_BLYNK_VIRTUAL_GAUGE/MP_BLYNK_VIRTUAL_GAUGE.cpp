#include "MP_BLYNK_VIRTUAL_GAUGE.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "no Blynk object";
const char error2[] PROGMEM = "Blynk is not ready";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK_VIRTUAL_GAUGE::ERRORS = errors_p;

MP_BLYNK_VIRTUAL_GAUGE::MP_BLYNK_VIRTUAL_GAUGE(uint8_t v_pin, MP_BLYNK* blynk) :
    v_pin(v_pin),
    blynk(blynk)
{

}

int MP_BLYNK_VIRTUAL_GAUGE::init() {
    if (!blynk)
        return 1;
    if (!blynk->isReady())
        return 2;
    return 0;
}

void MP_BLYNK_VIRTUAL_GAUGE::printStatus() {
    Serial.print(F("Current value = "));
    Serial.println(value);
}

void MP_BLYNK_VIRTUAL_GAUGE::update(unsigned long current_time) {
    blynk->update(millis());
}

void MP_BLYNK_VIRTUAL_GAUGE::setNumber(double value) {
    blynk->writeVirtualPin(v_pin, value);
}