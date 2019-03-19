#define IOT_HUB_SEND_GAP 100    // in ms

#include "MP_Azure_IoTHub_ESP8266.h"

MP_Azure_IoTHub_ESP8266::MP_Azure_IoTHub_ESP8266(const char* connectionString, MP_AZURE* azure)
    : connectionString(connectionString)
    , azure(azure)
    , messageHandle(NULL)
    , result(IOTHUB_CLIENT_CONFIRMATION_OK)
    , lastSendTime(0)
{    
}

int MP_Azure_IoTHub_ESP8266::init()
{
    // wait for wifi to be connected
    while (!azure->isConnected()) 
    {
        delay(100);
    }

    // wait until time is set
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    while (time(NULL) == 0) 
    {
        delay(1000);
    }

    // init IoTHub
    iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    if (iotHubClientHandle == NULL)
    {
        return ERR_CONNECT_SERVER;
    }

    return ERR_OK;
}

void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void *userContextCallback)
{
    *((IOTHUB_CLIENT_CONFIRMATION_RESULT*) userContextCallback) = result;
}

void MP_Azure_IoTHub_ESP8266::update(unsigned long currentTime)
{
    // TODO: use queue to store message instead of overriding the old message
    if (messageHandle != NULL && currentTime - lastSendTime > IOT_HUB_SEND_GAP)
    {
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, &result) != IOTHUB_CLIENT_OK)
        {
            // TODO: don't suspress error
        }

        IoTHubMessage_Destroy(messageHandle);
        messageHandle = NULL;
        lastSendTime = currentTime;
    }

    IoTHubClient_LL_DoWork(iotHubClientHandle);
    delay(10);
}

void MP_Azure_IoTHub_ESP8266::printStatus()
{
    if (result == IOTHUB_CLIENT_CONFIRMATION_OK)
    {
        Serial.println(F("No error is found"));
    }
    else
    {
        Serial.println(F("Found some errors while sending message to IoT Hub"));
    }
}

void MP_Azure_IoTHub_ESP8266::sendTelemetry(const char* message)
{
    messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char *) message, strlen(message));
    if (messageHandle == NULL)
    {
        // TODO: don't suspress error
    }
}

void MP_Azure_IoTHub_ESP8266::sendTelemetry(const Record& record)
{
    sendTelemetry(record.asJson().c_str());
}