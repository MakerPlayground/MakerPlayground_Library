#ifndef MP_NETPIE2020_ESP_H
#define MP_NETPIE2020_ESP_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include "MP_NETPIE2020.h"
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
#include <Wifi.h>
#endif
#include <PubSubClient.h>

#include <map>

class MP_NETPIE2020_ESP : public MP_NETPIE2020
{
public:
    MP_NETPIE2020_ESP(char clientId[], char token[], char secret[], char ssid[], char pass[]);

    int init();
    void update(unsigned long time);
    void printStatus();

    // chat and feed is not supported yet
    // TODO: handle error when publish
    void publish(char* topic, double v);
    void subscribe(char* topic);
    void unsubscribe(char* topic);

    double getValue(char* topic);

    static std::map<String, double> value;
    static std::map<String, bool> changed; 

private:
    char* clientId;
    char* token;
    char* secret;
    char* ssid;
    char* password;

    const char* mqtt_server = "broker.netpie.io";
    const int mqtt_port = 1883;

    WiFiClient deviceClient;
    PubSubClient client;

    unsigned long nextSendTime;
};

#endif