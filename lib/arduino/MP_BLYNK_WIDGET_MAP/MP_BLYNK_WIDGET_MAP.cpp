#include "MP_BLYNK_WIDGET_MAP.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "no Blynk object";
const char error2[] PROGMEM = "Blynk is not ready";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK_WIDGET_MAP::ERRORS = errors_p;

#define SEND_INTERVAL 100

MP_BLYNK_WIDGET_MAP::MP_BLYNK_WIDGET_MAP(uint8_t v_pin, uint8_t pinIndex, MP_BLYNK* blynk) :
    v_pin(v_pin),
    pinIndex(pinIndex),
    blynk(blynk)
{

}

int MP_BLYNK_WIDGET_MAP::init() {
    if (!blynk)
        return ERR_INTERNAL_ERROR;
    if (!blynk->isReady())
        return ERR_CLIENT_NOT_READY;
    return ERR_OK;
}

void MP_BLYNK_WIDGET_MAP::printStatus() {
    Serial.print(F("Current value = "));
    if (clearPinSentRequest) {
        Serial.println("None");
    } else {
        Serial.print(lat, 6); // Six digits
        Serial.print(F(", "));
        Serial.println(lon, 6); // Six digits
    }
}

void MP_BLYNK_WIDGET_MAP::update(unsigned long current_time) {
    blynk->update(millis());
    if (current_time - lastSentMillis > SEND_INTERVAL) {
        if (clearPinSentRequest) {
            blynk->writeVirtualPin(v_pin, "clr");
        } else {
            blynk->writeVirtualPin(v_pin, pinIndex, lat, lon, "value");
        }
        lastSentMillis = current_time;
    }
}

void MP_BLYNK_WIDGET_MAP::pinLocation(double latitude, double longitude) {
    lat = latitude;
    lon = longitude;
    clearPinSentRequest = false;
}

void MP_BLYNK_WIDGET_MAP::clearPin() {
    clearPinSentRequest = true;
}