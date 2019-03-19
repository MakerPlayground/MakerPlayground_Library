#include "MP_NETPIE_FEED.h"

#define SENT_INTERVAL 15000

MP_NETPIE_FEED::MP_NETPIE_FEED(char* feedId, char* apiKey, MP_NETPIE* netpie)
    : feedId(feedId)
    , apiKey(apiKey)
    , netpie(netpie)
{
}

int MP_NETPIE_FEED::init()
{
    return ERR_OK;
}
    
void MP_NETPIE_FEED::printStatus()
{
    Serial.print(F("data = "));
    Serial.print(current_value);
}

void MP_NETPIE_FEED::update(unsigned long currentTime)
{
    if (currentTime - lastSentTime > SENT_INTERVAL || lastSentTime == 0) {
        netpie->writeFeed(feedId, current_value, apiKey);
        lastSentTime = currentTime;
    }
}

void MP_NETPIE_FEED::sendTelemetry(Record record)
{
    current_value = record.asNetpieStr();
}