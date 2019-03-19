#ifndef MP_NETPIE_FEED_H
#define MP_NETPIE_FEED_H

#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

class MP_NETPIE_FEED
{
public:
    MP_NETPIE_FEED(char* feedId, char* apiKey, MP_NETPIE* netpie);

    int init();
    void update(unsigned long time);
    void printStatus();

    void sendTelemetry(Record record);

private:
    char* feedId;
    char* apiKey;
    char* data;
    unsigned long lastSentTime = 0;
    String current_value;
    MP_NETPIE* netpie;
};

#endif 