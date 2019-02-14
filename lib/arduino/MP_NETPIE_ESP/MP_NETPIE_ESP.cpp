#include "MP_NETPIE_ESP.h"

#define PUBLISH_INTERVAL 500

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE::ERRORS = errors_p;

std::map<String, double> MP_NETPIE_ESP::value;
std::map<String, bool> MP_NETPIE_ESP::changed;

// function to be called when message arrives
void onMsghandler(char* topic, uint8_t* msg, unsigned int msglen) 
{
    msg[msglen] = '\0';
    String topic_str = topic;
    if (topic_str.startsWith("/")) {
        topic_str = topic_str.substring(topic_str.indexOf('/', 1));
        MP_NETPIE_ESP::value[topic_str] = atof((char *) msg);
    }
}

MP_NETPIE_ESP::MP_NETPIE_ESP(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[])
    : appId(appId)
    , key(key)
    , secret(secret)
    , alias(alias)
    , ssid(ssid)
    , password(pass)
    , microgear(client)
    , nextSendTime(0)
{
}

int MP_NETPIE_ESP::init()
{
    microgear.on(MESSAGE, onMsghandler);

    // connect to wifi
    WiFi.mode(WIFI_STA);
    if (WiFi.begin(ssid, password)) 
    {
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
        }
    }

    // initialize the microgear
    microgear.init(key, secret, alias);
    
    // connect to NETPIE
    microgear.connect(appId);

    return 0;
}

void MP_NETPIE_ESP::printStatus()
{
    if (!microgear.connected())
    {
        Serial.println("Can't connected to the NETPIE server");
    }
}

void MP_NETPIE_ESP::update(unsigned long time)
{
    if (microgear.connected())
    {
        // this method need to be called regularly to avoid connection lost
        microgear.loop();

        // publish every some specified interval
        if (nextSendTime <= time)
        {
            for (const auto& c : changed) 
            {
                if (c.second)
                {
                    microgear.publish((char*) (c.first.c_str()), value[c.first]);
                    changed[c.first] = false;
                }
            }
            nextSendTime = time + PUBLISH_INTERVAL;
        }
    } 
    else
    {
        microgear.connect(appId);
    }
}

void MP_NETPIE_ESP::publish(char* topic, double v)
{
    value[String(topic)] = v;
    changed[String(topic)] = true;
}

void MP_NETPIE_ESP::subscribe(char* topic)
{
    value[String(topic)] = 0;
    microgear.subscribe(topic);
}

void MP_NETPIE_ESP::unsubscribe(char* topic)
{
    microgear.unsubscribe(topic);
}

double MP_NETPIE_ESP::getValue(char* topic)
{
    return value[String(topic)];
}

void MP_NETPIE_ESP::writeFeed(char* feedId, String data, char* apiKey) {
    microgear.writeFeed(feedId, data, apiKey);
}