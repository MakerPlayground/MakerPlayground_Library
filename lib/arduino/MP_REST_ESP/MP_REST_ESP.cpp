#include "MP_REST_ESP.h"

MP_REST_ESP::MP_REST_ESP(const char* ssid, const char* pass)
    : ssid(ssid)
    , pass(pass)
{    
}

int MP_REST_ESP::init()
{
    WiFi.begin(ssid, pass);
    return ERR_OK;
}

void MP_REST_ESP::update(unsigned long currentTime)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        delay(25);
    }
}

void MP_REST_ESP::printStatus()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Wifi connected");
    }
    else 
    {
        Serial.println("Wifi is not connected");
    }
}

bool MP_REST_ESP::isConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}