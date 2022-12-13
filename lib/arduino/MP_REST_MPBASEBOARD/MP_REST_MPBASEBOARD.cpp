#include "MP_REST_MPBASEBOARD.h"

MP_REST_MPBASEBOARD::MP_REST_MPBASEBOARD(const char* ssid, const char* pass)
    : ssid(ssid)
    , pass(pass)
{    
}

bool MP_REST_MPBASEBOARD::checkResponse()
{
    return Serial1.readStringUntil('\n').equals("OK\r");
}

int MP_REST_MPBASEBOARD::init()
{
    Serial1.begin(115200);
    Serial1.setTimeout(15000);
    delay(10);

    // connect to wifi and wait for response
    Serial1.print(F("W\r"));
    Serial1.print(ssid);
    Serial1.print(F("\r"));
    Serial1.println(pass);
    if (!checkResponse())
    {
        return MP_ERR_CONNECT_WIFI;
    }
    return MP_ERR_OK;
}

void MP_REST_MPBASEBOARD::update(unsigned long currentTime)
{
}

void MP_REST_MPBASEBOARD::printStatus()
{
    // TODO: print status
}

bool MP_REST_MPBASEBOARD::isConnected()
{
    // we should not always return true
    return true;
}