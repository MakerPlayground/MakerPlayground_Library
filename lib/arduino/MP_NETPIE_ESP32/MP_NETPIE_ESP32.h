#ifndef MP_NETPIE_ESP32_H
#define MP_NETPIE_ESP32_H

#include "MP_NETPIE.h"
#include <Wifi.h>
#include <MicroGear.h>

#include <map>

class MP_NETPIE_ESP32 : public MP_NETPIE
{
public:
    MP_NETPIE_ESP32(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[]);

    int init();
    void update(unsigned long time);
    void printStatus();

    // chat and feed is not supported yet
    // TODO: handle error when publish
    void publish(char* topic, double v);
    void subscribe(char* topic);
    void unsubscribe(char* topic);

    double getValue(char* topic);

    static std::map<char*, double> value;
    static std::map<char*, bool> changed; 

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