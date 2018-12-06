#ifndef MP_NETPIE_ESP8266_H
#define MP_NETPIE_ESP8266_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include "MP_NETPIE.h"
#include <ESP8266WiFi.h>
#include <MicroGear.h>

#include <map>

class MP_NETPIE_ESP8266 : public MP_NETPIE
{
public:
    MP_NETPIE_ESP8266(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[]);

    int init();
    void update(unsigned long time);
    void printStatus();

    // chat and feed is not supported yet
    // TODO: handle error when publish
    void publish(char* topic, double v);
    void subscribe(char* topic);
    void unsubscribe(char* topic);

    double getValue(char* topic);

    MicroGear getMicrogear();
    static std::map<String, double> value;
    static std::map<String, bool> changed; 

private:
    char* appId;
    char* key;
    char* secret;
    char* alias;
    char* ssid;
    char* password;

    WiFiClient client;
    MicroGear microgear;

    unsigned long nextSendTime;
};

#endif