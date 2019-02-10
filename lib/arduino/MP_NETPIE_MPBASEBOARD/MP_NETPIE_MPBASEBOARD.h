#ifndef MP_NETPIE_MPBASEBOARD_H
#define MP_NETPIE_MPBASEBOARD_H

#include "Arduino.h"
#include "MP_DEVICE.h"
#include "MP_NETPIE.h"

struct NetpieTopic
{
    char* name;
    double value;
    NetpieTopic* next;
};

class MP_NETPIE_MPBASEBOARD : public MP_NETPIE
{
public:
    MP_NETPIE_MPBASEBOARD(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[]);

    int init();
    void update(unsigned long time);
    void printStatus();

    // chat and feed is not supported yet
    // TODO: handle error when publish
    void publish(char* topic, double v);
    void subscribe(char* topic);
    void unsubscribe(char* topic);

    double getValue(char* topic);
    void writeFeed(char* feedId, String data, char* apiKey);

private:
    bool checkResponse();

    char* appId;
    char* key;
    char* secret;
    char* alias;
    char* ssid;
    char* password;

    NetpieTopic* value;

    unsigned long nextReceiveTime;
};

#endif