#include "MP_REST_WIOTERMINAL.h"
#include <SPI.h>
#include <Adafruit_ZeroDMA.h>
#include "Seeed_mbedtls.h"
#include "Seeed_FS.h"
#include "rpcWiFi.h"

MP_REST_WIOTERMINAL::MP_REST_WIOTERMINAL(const char* ssid, const char* pass)
    : ssid(ssid)
    , pass(pass)
{    
}

int MP_REST_WIOTERMINAL::init()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
    return MP_ERR_OK;
}

void MP_REST_WIOTERMINAL::update(unsigned long currentTime)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        delay(25);
    }
}

void MP_REST_WIOTERMINAL::printStatus()
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

bool MP_REST_WIOTERMINAL::isConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}