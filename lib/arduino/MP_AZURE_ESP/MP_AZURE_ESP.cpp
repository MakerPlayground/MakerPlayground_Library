#include "MP_AZURE_ESP.h"

MP_AZURE_ESP::MP_AZURE_ESP(const char* ssid, const char* pass)
    : ssid(ssid)
    , pass(pass)
{    
}

int MP_AZURE_ESP::init()
{
    WiFi.begin(ssid, pass);
    return ERR_OK;
}

void MP_AZURE_ESP::update(unsigned long currentTime)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        delay(25);
    }
}

void MP_AZURE_ESP::printStatus()
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

bool MP_AZURE_ESP::isConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}