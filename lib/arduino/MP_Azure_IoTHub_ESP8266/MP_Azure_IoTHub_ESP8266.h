#ifndef MP_Azure_IoTHub_ESP8266_H
#define MP_Azure_IoTHub_ESP8266_H

#include <Arduino.h>
#include "MP_DEVICE.h"
#include "MP_AZURE.h"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>

class MP_Azure_IoTHub_ESP8266
{
public:
    MP_Azure_IoTHub_ESP8266(const char* connectionString, MP_AZURE* azure);
    int init();
	void update(unsigned long currentTime);
	void printStatus();
    static const char* const* ERRORS;
    
    void sendTelemetry(const Record& record);
    void sendTelemetry(const char* message);

private:
    const char* connectionString;
    MP_AZURE* azure;

    IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
    IOTHUB_MESSAGE_HANDLE messageHandle;
    IOTHUB_CLIENT_CONFIRMATION_RESULT result;

    unsigned long lastSendTime;
};

#endif