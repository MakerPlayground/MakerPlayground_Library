#include "MP_NETPIE_ESP8266.h"

#define PUBLISH_INTERVAL 500

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_NETPIE::ERRORS = errors_p;

std::map<char*, double> MP_NETPIE_ESP8266::value;
std::map<char*, bool> MP_NETPIE_ESP8266::changed; 

// function to be called when message arrives
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
    msg[msglen] = '\0';
    MP_NETPIE_ESP8266::value[topic] = atof((char *) msg);
}

// function to be called when this microgear is connected to NETPIE
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    // Set the alias of this microgear ALIAS
    // microgear.setAlias(ALIAS);
}

MP_NETPIE_ESP8266::MP_NETPIE_ESP8266(char appId[], char key[], char secret[], char alias[], char ssid[], char pass[]) 
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

int MP_NETPIE_ESP8266::init() 
{
    microgear.on(MESSAGE, onMsghandler);
    microgear.on(CONNECTED, onConnected);

    // connect to wifi
    Serial.print("Connecting to wifi");
    Serial.println(ssid);
    Serial.println(password);
    WiFi.mode(WIFI_STA);
    if (WiFi.begin(ssid, password)) 
    {
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
            Serial.print(".");
        }
    }
    Serial.println("\nWiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // initialize the microgear
    microgear.init(key, secret, alias);
    
    // connect to NETPIE
    microgear.connect(appId);

    return 0;
}

void MP_NETPIE_ESP8266::printStatus() {
    
}

void MP_NETPIE_ESP8266::update(unsigned long time)
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
                    microgear.publish(c.first, value[c.first]);
                    changed[c.first] = false;
                }
            }
            nextSendTime = time + PUBLISH_INTERVAL;
        }
    } 
    else
    {
        Serial.println("Connection lost, reconnecting...");
        microgear.connect(appId);
    } 
}

void MP_NETPIE_ESP8266::publish(char* topic, double v) 
{
    value[topic] = v;
    changed[topic] = true;
}

void MP_NETPIE_ESP8266::subscribe(char* topic)
{
    value[topic] = 0;
    microgear.subscribe(topic);
}

void MP_NETPIE_ESP8266::unsubscribe(char* topic)
{
    microgear.unsubscribe(topic);
}

double MP_NETPIE_ESP8266::getValue(char* topic)
{
    return value[topic];
}