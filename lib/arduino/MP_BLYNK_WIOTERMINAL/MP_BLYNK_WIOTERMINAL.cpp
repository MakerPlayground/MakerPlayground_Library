/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)
#define _BV( bit ) ( 1<<(bit) )     // polyfill as this macro is not available in SAMD51 arduino library

#include "MP_BLYNK_WIOTERMINAL.h"
#include <SPI.h>
#include <Adafruit_ZeroDMA.h>
#include "Seeed_mbedtls.h"
#include "Seeed_FS.h"
#include "rpcWiFi.h"
#include <WiFiClient.h>
#include <BlynkSimpleWioTerminal.h>

double MP_BLYNK_WIOTERMINAL::value[8];
uint8_t MP_BLYNK_WIOTERMINAL::valueChanged;

MP_BLYNK_WIOTERMINAL::MP_BLYNK_WIOTERMINAL(char* auth, char* templateID, char* ssid, char* pass)
    : auth(auth)
    , templateID(templateID)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        MP_BLYNK_WIOTERMINAL::value[i] = 0;
    }
}

int MP_BLYNK_WIOTERMINAL::init()
{
    if (!connectWifi()) {
        return MP_ERR_CONNECT_WIFI;
    }

    Blynk.config(auth, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT, templateID);

    if (!Blynk.connect()) {
        return MP_ERR_CONNECT_SERVER;
    }
    
    return MP_ERR_OK;
}

bool MP_BLYNK_WIOTERMINAL::connectWifi()
{
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(2000);

    WiFi.begin(this->ssid, this->pass);
    
    int retry = 50;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        if (retry == 0) {
            return false;
        }
        retry--;
    }
    return true;
}

void MP_BLYNK_WIOTERMINAL::update(unsigned long time) 
{
    Blynk.run();
    // push value waited to be push to blynk server
    if (time - lastSendMillis > SEND_GAP) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            if (MP_BLYNK_WIOTERMINAL::valueChanged & (1 << i)) 
            {
                Blynk.virtualWrite(i, MP_BLYNK_WIOTERMINAL::value[i]);
                MP_BLYNK_WIOTERMINAL::valueChanged &= ~(1 << i);
            }
        }
        lastSendMillis = time;
    }
}

void MP_BLYNK_WIOTERMINAL::printStatus()
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

bool MP_BLYNK_WIOTERMINAL::isReady()
{
    return WiFi.status() == WL_CONNECTED;
}

int MP_BLYNK_WIOTERMINAL::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_WIOTERMINAL::value[pin];
}

void MP_BLYNK_WIOTERMINAL::writeVirtualPin(uint8_t pin, double value)
{
    MP_BLYNK_WIOTERMINAL::value[pin] = value;
    MP_BLYNK_WIOTERMINAL::valueChanged |= (1 << pin);
}

void MP_BLYNK_WIOTERMINAL::writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4)
{
    Blynk.virtualWrite(pin, val1, val2, val3, val4);
}

void MP_BLYNK_WIOTERMINAL::writeVirtualPin(uint8_t pin, char* val1)
{
    Blynk.virtualWrite(pin, val1);
}

void MP_BLYNK_WIOTERMINAL::notify(const char* msg) {
    Blynk.notify(msg);
}

bool MP_BLYNK_WIOTERMINAL::checkVirtualPinValue(uint8_t pin, int value)
{
    return MP_BLYNK_WIOTERMINAL::value[pin] == value;
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_WIOTERMINAL::getVirtualPin7()
{
    return this->readVirtualPin(7);
}

BLYNK_READ(V0) 
{
    Blynk.virtualWrite(0, MP_BLYNK_WIOTERMINAL::value[0]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(0);
}

BLYNK_READ(V1) 
{
    Blynk.virtualWrite(1, MP_BLYNK_WIOTERMINAL::value[1]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(1);
}

BLYNK_READ(V2) 
{
    Blynk.virtualWrite(2, MP_BLYNK_WIOTERMINAL::value[2]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(2);
}

BLYNK_READ(V3) 
{
    Blynk.virtualWrite(3, MP_BLYNK_WIOTERMINAL::value[3]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(3);
}

BLYNK_READ(V4) 
{
    Blynk.virtualWrite(4, MP_BLYNK_WIOTERMINAL::value[4]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(4);
}

BLYNK_READ(V5) 
{
    Blynk.virtualWrite(5, MP_BLYNK_WIOTERMINAL::value[5]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(5);
}

BLYNK_READ(V6) 
{
    Blynk.virtualWrite(6, MP_BLYNK_WIOTERMINAL::value[6]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(6);
}

BLYNK_READ(V7) 
{
    Blynk.virtualWrite(7, MP_BLYNK_WIOTERMINAL::value[7]);
    MP_BLYNK_WIOTERMINAL::valueChanged &= ~_BV(7);
}

BLYNK_WRITE(V0) 
{
    MP_BLYNK_WIOTERMINAL::value[0] = param.asInt();
}

BLYNK_WRITE(V1) 
{
    MP_BLYNK_WIOTERMINAL::value[1] = param.asInt();
}

BLYNK_WRITE(V2) 
{
    MP_BLYNK_WIOTERMINAL::value[2] = param.asInt();
}

BLYNK_WRITE(V3) 
{
    MP_BLYNK_WIOTERMINAL::value[3] = param.asInt();
}

BLYNK_WRITE(V4) 
{
    MP_BLYNK_WIOTERMINAL::value[4] = param.asInt();
}

BLYNK_WRITE(V5) 
{
    MP_BLYNK_WIOTERMINAL::value[5] = param.asInt();
}

BLYNK_WRITE(V6) 
{
    MP_BLYNK_WIOTERMINAL::value[6] = param.asInt();
}

BLYNK_WRITE(V7) 
{
    MP_BLYNK_WIOTERMINAL::value[7] = param.asInt();
}