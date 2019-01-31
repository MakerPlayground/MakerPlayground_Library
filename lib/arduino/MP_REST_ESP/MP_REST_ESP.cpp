#include "MP_REST_ESP.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};
const char* const* MP_REST::ERRORS = errors_p;

MP_REST_ESP::MP_REST_ESP(const char* ssid, const char* pass)
    : ssid(ssid)
    , pass(pass)
{    
}

int MP_REST_ESP::init()
{
    // WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    // TODO: allow system to work without wifi connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    return 0;
}

void MP_REST_ESP::update(unsigned long currentTime)
{
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