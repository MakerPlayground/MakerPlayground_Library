#include "MP_BLYNK_NOTIFICATION.h"

MP_BLYNK_NOTIFICATION::MP_BLYNK_NOTIFICATION(MP_BLYNK* blynk) :
    blynk(blynk)
{

}

int MP_BLYNK_NOTIFICATION::init() {
    if (!blynk)
        return ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return ERR_CLIENT_NOT_READY;
    return ERR_OK;
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