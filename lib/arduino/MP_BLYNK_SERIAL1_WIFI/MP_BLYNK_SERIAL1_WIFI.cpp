/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial
#define ESP8266_BAUD 115200
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)
#define PING_GAP 30000  // in ms (ping every 30 secs)

#include "MP_BLYNK_SERIAL1_WIFI.h"
#include <BlynkSimpleShieldEsp8266.h>

double MP_BLYNK_SERIAL1_WIFI::value[8];
uint8_t MP_BLYNK_SERIAL1_WIFI::valueChanged;

MP_BLYNK_SERIAL1_WIFI::MP_BLYNK_SERIAL1_WIFI(char* auth, char* ssid, char* pass)
    : wifi(&Serial1)
    , auth(auth)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
    , lastPingMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        MP_BLYNK_SERIAL1_WIFI::value[i] = 0;
    }
}

void MP_BLYNK_SERIAL1_WIFI::ledOn() {
    // rev 0 board
    Serial1.println(F("AT+CIOWRITE=0,0"));
    recvString("OK", "ERROR", 1000);
    // rev1 board
    Serial1.println(F("AT+SYSGPIOWRITE=0,0"));
    recvString("OK", "ERROR", 1000);
}

void MP_BLYNK_SERIAL1_WIFI::ledOff() {
    // rev 0 board
    Serial1.println(F("AT+CIOWRITE=0,1"));
    recvString("OK", "ERROR", 1000);
    // rev1 board
    Serial1.println(F("AT+SYSGPIOWRITE=0,1"));
    recvString("OK", "ERROR", 1000);
}

String MP_BLYNK_SERIAL1_WIFI::recvString(String target1, String target2, uint32_t timeout)
{
    String data;
    char a;
    unsigned long start = millis();
    while (millis() - start < timeout) {
        while(Serial1.available() > 0) {
            a = Serial1.read();
            if(a == '\0') continue;
            data += a;
            if (data.indexOf(target1) != -1) {
                return data;
            } else if (data.indexOf(target2) != -1) {
                return data;
            } /*else if (checkIPD(data)) {
                data = "";
            }*/
        }
    }
    return data;
}

int MP_BLYNK_SERIAL1_WIFI::init() 
{
    Serial1.begin(115200);
    delay(10);
    // setup gpio (rev 1 board only)
    Serial1.println(F("AT+SYSGPIODIR=0,1"));
    recvString("OK", "ERROR", 1000);
    // connect to wifi and blynk server
    
    return initConnection();
}

bool MP_BLYNK_SERIAL1_WIFI::isReady()
{
    return testPing();
}

int MP_BLYNK_SERIAL1_WIFI::initConnection()
{
    // initial wifi
    Blynk.config(this->wifi, this->auth, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);

    if (!connectWifi()) {
        return MP_ERR_CONNECT_WIFI;
    }
    
    if (!testPing()) {
        return MP_ERR_CONNECT_SERVER;
    }

    if (!Blynk.connect()) {
        return MP_ERR_CONNECT_SERVER;
    }

    return MP_ERR_OK;
}


bool MP_BLYNK_SERIAL1_WIFI::connectWifi()
{
    ledOff();
    int retry = 5;
    while (!Blynk.connectWiFi(this->ssid, this->pass)) {
        delay(1);
        if (retry == 0) {
            return false;
        }
        retry--;
    }
    ledOn();
    return true;
}

bool MP_BLYNK_SERIAL1_WIFI::testPing()
{
    int pingRetry = 5;
    while (pingRetry > 0) {
        // test connection
        Serial1.println(F("AT+PING=\"4.2.2.2\""));
        String data = recvString("OK", "ERROR", 5000);
        if (data.indexOf("OK") != -1) {
            return true;
        }
        pingRetry--;
        delay(PING_GAP);
    }
    return false;
}

void MP_BLYNK_SERIAL1_WIFI::printStatus()
{
    Serial.print(F("Current virtual pin status = "));
    Serial.print(getVirtualPin0());
    Serial.print(F(" "));
    Serial.print(getVirtualPin1());
    Serial.print(F(" "));
    Serial.print(getVirtualPin2());
    Serial.print(F(" "));
    Serial.print(getVirtualPin3());
    Serial.print(F(" "));
    Serial.print(getVirtualPin4());
    Serial.print(F(" "));
    Serial.print(getVirtualPin5());
    Serial.print(F(" "));
    Serial.print(getVirtualPin6());
    Serial.print(F(" "));
    Serial.print(getVirtualPin7());
    Serial.println();
}

void MP_BLYNK_SERIAL1_WIFI::update(unsigned long time) 
{
    Blynk.run();
    // push value waited to be push to blynk server
    if (time - lastSendMillis > SEND_GAP) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            if (MP_BLYNK_SERIAL1_WIFI::valueChanged & (1 << i)) 
            {
                Blynk.virtualWrite(i, MP_BLYNK_SERIAL1_WIFI::value[i]);
                MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~(1 << i);
            }
        }
        lastSendMillis = time;
    }
    // ping to check network connection
    if (time - lastPingMillis > PING_GAP)
    {
        if (!testPing()) {
            initConnection();
        }
        lastPingMillis = time;
    }
}

int MP_BLYNK_SERIAL1_WIFI::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_SERIAL1_WIFI::value[pin];
}

void MP_BLYNK_SERIAL1_WIFI::writeVirtualPin(uint8_t pin, double value)
{
    MP_BLYNK_SERIAL1_WIFI::value[pin] = value;
    MP_BLYNK_SERIAL1_WIFI::valueChanged |= (1 << (pin));
}

void MP_BLYNK_SERIAL1_WIFI::writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4)
{
    Blynk.virtualWrite(pin, val1, val2, val3, val4);
}

void MP_BLYNK_SERIAL1_WIFI::writeVirtualPin(uint8_t pin, char* val1)
{
    Blynk.virtualWrite(pin, val1);
}

void MP_BLYNK_SERIAL1_WIFI::notify(char* msg) {
    Blynk.notify(msg);
}

bool MP_BLYNK_SERIAL1_WIFI::checkVirtualPinValue(uint8_t pin, int value)
{
    return MP_BLYNK_SERIAL1_WIFI::value[pin] == value;
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_SERIAL1_WIFI::getVirtualPin7()
{
    return this->readVirtualPin(7);
}

BLYNK_READ(V0) 
{
    Blynk.virtualWrite(0, MP_BLYNK_SERIAL1_WIFI::value[0]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(0);
}

BLYNK_READ(V1) 
{
    Blynk.virtualWrite(1, MP_BLYNK_SERIAL1_WIFI::value[1]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(1);
}

BLYNK_READ(V2) 
{
    Blynk.virtualWrite(2, MP_BLYNK_SERIAL1_WIFI::value[2]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(2);
}

BLYNK_READ(V3) 
{
    Blynk.virtualWrite(3, MP_BLYNK_SERIAL1_WIFI::value[3]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(3);
}

BLYNK_READ(V4) 
{
    Blynk.virtualWrite(4, MP_BLYNK_SERIAL1_WIFI::value[4]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(4);
}

BLYNK_READ(V5) 
{
    Blynk.virtualWrite(5, MP_BLYNK_SERIAL1_WIFI::value[5]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(5);
}

BLYNK_READ(V6) 
{
    Blynk.virtualWrite(6, MP_BLYNK_SERIAL1_WIFI::value[6]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(6);
}

BLYNK_READ(V7) 
{
    Blynk.virtualWrite(7, MP_BLYNK_SERIAL1_WIFI::value[7]);
    MP_BLYNK_SERIAL1_WIFI::valueChanged &= ~_BV(7);
}

BLYNK_WRITE(V0) 
{
    MP_BLYNK_SERIAL1_WIFI::value[0] = param.asInt();
}

BLYNK_WRITE(V1) 
{
    MP_BLYNK_SERIAL1_WIFI::value[1] = param.asInt();
}

BLYNK_WRITE(V2) 
{
    MP_BLYNK_SERIAL1_WIFI::value[2] = param.asInt();
}

BLYNK_WRITE(V3) 
{
    MP_BLYNK_SERIAL1_WIFI::value[3] = param.asInt();
}

BLYNK_WRITE(V4) 
{
    MP_BLYNK_SERIAL1_WIFI::value[4] = param.asInt();
}

BLYNK_WRITE(V5) 
{
    MP_BLYNK_SERIAL1_WIFI::value[5] = param.asInt();
}

BLYNK_WRITE(V6) 
{
    MP_BLYNK_SERIAL1_WIFI::value[6] = param.asInt();
}

BLYNK_WRITE(V7) 
{
    MP_BLYNK_SERIAL1_WIFI::value[7] = param.asInt();
}