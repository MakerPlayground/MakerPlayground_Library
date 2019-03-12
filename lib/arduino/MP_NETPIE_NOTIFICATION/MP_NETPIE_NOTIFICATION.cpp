#include "MP_NETPIE_NOTIFICATION.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE_NOTIFICATION::ERRORS = errors_p;

MP_NETPIE_NOTIFICATION::MP_NETPIE_NOTIFICATION(MP_NETPIE* netpie)
    : netpie(netpie)
{

}

int MP_NETPIE_NOTIFICATION::init()
{
    return 0;
}

void MP_NETPIE_NOTIFICATION::printStatus() {
    Serial.print("notify is ready.");
}

void MP_NETPIE_NOTIFICATION::update(unsigned long current_time) {
    netpie->update(millis());
}

void MP_NETPIE_NOTIFICATION::notify(char* msg) {
    netpie->notify(msg);
}