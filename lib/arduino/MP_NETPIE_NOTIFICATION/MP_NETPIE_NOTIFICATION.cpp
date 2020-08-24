#include "MP_NETPIE_NOTIFICATION.h"

MP_NETPIE_NOTIFICATION::MP_NETPIE_NOTIFICATION(MP_NETPIE* netpie)
    : netpie(netpie)
{

}

int MP_NETPIE_NOTIFICATION::init()
{
    return MP_ERR_OK;
}

void MP_NETPIE_NOTIFICATION::printStatus() {
    Serial.print("notify is ready.");
}

void MP_NETPIE_NOTIFICATION::update(unsigned long current_time) {
    netpie->update(millis());
}

void MP_NETPIE_NOTIFICATION::notify(const char* msg) {
    netpie->notify(msg);
}