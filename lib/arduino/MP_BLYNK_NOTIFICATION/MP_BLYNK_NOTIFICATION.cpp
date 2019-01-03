#include "MP_BLYNK_NOTIFICATION.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "no Blynk object";
const char error2[] PROGMEM = "Blynk is not ready";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK_NOTIFICATION::ERRORS = errors_p;

MP_BLYNK_NOTIFICATION::MP_BLYNK_NOTIFICATION(MP_BLYNK* blynk) :
    blynk(blynk)
{

}

int MP_BLYNK_NOTIFICATION::init() {
    if (!blynk)
        return 1;
    if (!blynk->isReady())
        return 2;
    return 0;
}

void MP_BLYNK_NOTIFICATION::printStatus() {
    Serial.print("notify is ready.");
}

void MP_BLYNK_NOTIFICATION::update(unsigned long current_time) {
    blynk->update(millis());
}

void MP_BLYNK_NOTIFICATION::notify(char* msg) {
    blynk->notify(msg);
}