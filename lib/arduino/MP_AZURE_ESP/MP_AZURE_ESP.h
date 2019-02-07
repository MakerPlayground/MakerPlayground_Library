#ifndef MP_AZURE_ESP_H
#define MP_AZURE_ESP_H

#include <Arduino.h>
#include "MP_DEVICE.h"
#include "MP_AZURE.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

class MP_AZURE_ESP : public MP_AZURE
{
public:
    MP_AZURE_ESP(const char* ssid, const char* pass);
    int init();
	void update(unsigned long currentTime);
	void printStatus();

    bool isConnected();

private:
    const char* ssid;
    const char* pass;
};

#endif