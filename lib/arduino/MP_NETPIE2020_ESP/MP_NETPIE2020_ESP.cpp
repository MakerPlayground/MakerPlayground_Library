#include "MP_NETPIE2020_ESP.h"

#define PUBLISH_INTERVAL 1000

std::map<String, double> MP_NETPIE2020_ESP::value;
std::map<String, bool> MP_NETPIE2020_ESP::changed;

// function to be called when message arrives
void onMsghandler(char* topic, uint8_t* msg, unsigned int msglen) 
{
  String message = "";
    for (int i = 0; i < msglen; i++) {
        message = message + (char)msg[i];
    }
    MP_NETPIE2020_ESP::value[String(topic)] = atof(message.c_str());
}

MP_NETPIE2020_ESP::MP_NETPIE2020_ESP(char clientId[], char token[], char secret[], char ssid[], char pass[])
    : clientId(clientId)
    , token(token)
    , secret(secret)
    , ssid(ssid)
    , password(pass)
    , client(deviceClient)
    , nextSendTime(0)
{
}

int MP_NETPIE2020_ESP::init()
{    
    // connect to wifi
    WiFi.mode(WIFI_STA);
    if (WiFi.begin(ssid, password)) 
    {
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
        }
    }
    else {
        return ERR_CONNECT_WIFI;
    }

    // set MQTT server and port 
    client.setServer(mqtt_server, mqtt_port);

    // set call black function
    client.setCallback(onMsghandler);

    // connect to NETPIE
    client.connect(clientId, token, secret);

    return ERR_OK;
}

void MP_NETPIE2020_ESP::printStatus()
{
    if (!client.connected())
    {
        Serial.println("Can't connected to the NETPIE server");
    }
}

void MP_NETPIE2020_ESP::update(unsigned long time)
{
    if (!client.connected()) {
        while (!client.connected()) {
            if (!client.connect(clientId, token, secret)) {
                delay(5000);
            } 
        }
    }
    if (nextSendTime <= time)
    {
        for (const std::pair<String, bool>& c : changed) 
        {
            if (c.second)
            {
                client.publish(c.first.c_str(), String(value[c.first], 3).c_str());
                changed[c.first] = false;
            }
            Serial.println(value[c.first]);
        }
        nextSendTime = time + PUBLISH_INTERVAL;
        
    }
    client.loop();
}

void MP_NETPIE2020_ESP::publish(char* topic, double v)
{
    value[String(topic)] = v;
    changed[String(topic)] = true;
}

void MP_NETPIE2020_ESP::subscribe(char* topic)
{
    value[String(topic)] = 0;
    client.subscribe(topic);
}

void MP_NETPIE2020_ESP::unsubscribe(char* topic)
{
    client.unsubscribe(topic);
}

double MP_NETPIE2020_ESP::getValue(char* topic)
{
    return value[String(topic)];
}