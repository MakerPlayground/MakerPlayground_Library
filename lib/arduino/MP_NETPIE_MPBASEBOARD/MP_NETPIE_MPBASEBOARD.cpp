#include "MP_NETPIE_MPBASEBOARD.h"

#define PUBLISH_INTERVAL 500

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't connect to internet";
const char error2[] PROGMEM = "Can't connect to NETPIE Server";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_NETPIE_MPBASEBOARD::ERRORS = errors_p;

MP_NETPIE_MPBASEBOARD::MP_NETPIE_MPBASEBOARD(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[])
    : appId(appId)
    , key(key)
    , secret(secret)
    , alias(alias)
    , ssid(ssid)
    , password(pass)
    , nextReceiveTime(0)
    , value(NULL)
{
}

int MP_NETPIE_MPBASEBOARD::init()
{
    Serial1.begin(115200);
    Serial1.setTimeout(5000);
    delay(10);

    // connect to wifi and wait for response
    Serial1.print(F("W,"));
    Serial1.print(ssid);
    Serial1.print(F(","));
    Serial1.println(password);
    if (!checkResponse())
    {
        return 1;
    }

    // connect to netpie
    Serial1.print(F("N,"));
    Serial1.print(key);
    Serial1.print(F(","));
    Serial1.print(secret);
    Serial1.print(F(","));
    Serial1.print(alias);
    Serial1.print(F(","));
    Serial1.println(appId);
    if (!checkResponse())
    {
        return 2;
    }

    return 0;
}

void MP_NETPIE_MPBASEBOARD::printStatus()
{
}

bool MP_NETPIE_MPBASEBOARD::checkResponse()
{
    return Serial1.readStringUntil('\n').equals("OK\r");
}

void MP_NETPIE_MPBASEBOARD::update(unsigned long time)
{
    // publish every some specified interval
    if (nextReceiveTime <= time)
    {
        NetpieTopic* currentValue = value;
        while (currentValue != NULL)
        {
            Serial1.print(F("G,"));
            Serial1.println(currentValue->name);
            currentValue->value = Serial1.parseInt();
            checkResponse();
            currentValue = currentValue->next;
        }
        nextReceiveTime = time + PUBLISH_INTERVAL;
    }
}

void MP_NETPIE_MPBASEBOARD::publish(char* topic, double v)
{
    Serial1.print(F("P,"));
    Serial1.print(topic);
    Serial1.print(F(","));
    Serial1.println(String(v));
    checkResponse();
}

void MP_NETPIE_MPBASEBOARD::subscribe(char* topic)
{
    Serial1.print(F("S,"));
    Serial1.println(topic);
    checkResponse();

    // insert new topic at the head of the link listed
    NetpieTopic* newTopic = new NetpieTopic();
    newTopic->name = strdup(topic);
    newTopic->value = 0;
    newTopic->next = value;
    value = newTopic;
}

void MP_NETPIE_MPBASEBOARD::unsubscribe(char* topic)
{
    Serial1.print(F("U,"));
    Serial1.println(topic);
    checkResponse();
}

double MP_NETPIE_MPBASEBOARD::getValue(char* topic)
{
    // search for NetpieTopic with the same topic and return it's value
    NetpieTopic* currentValue = value;
    while (currentValue != NULL)
    {
        if (strcmp(currentValue->name, topic) == 0)
        {
            return currentValue->value;
        }
        currentValue = currentValue->next;
    }
    return 0;
}

void MP_NETPIE_MPBASEBOARD::writeFeed(char* feedId, String data, char* apiKey)
{
    // TODO: implement write feed for MP
}