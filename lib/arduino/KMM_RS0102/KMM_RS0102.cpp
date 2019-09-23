#include "KMM_RS0102.h"

KMM_RS0102::KMM_RS0102(uint8_t device_id)
	:device_id(device_id)
{
}

int KMM_RS0102::init()
{
	return ERR_OK;
}

void KMM_RS0102::update(unsigned long current_time)
{
    if (current_time - last_millis > 200)
    {   
        node.begin(device_id, Serial);
        // Reading sensor modbus device , RS1-0102
        result = node.readHoldingRegisters(0x0000,2);

        data = node.getResponseBuffer(0x00);
        celcius = 0.1 * data; // String(data/10)+"."+String(data%10);
        Serial.print("Device ID#");
        Serial.print(device_id);
        Serial.print("\tTemperature is " + String(celcius) + "°C");

        data = node.getResponseBuffer(0x01);
        humid = 0.1 * data; //String(data/10)+"."+String(data%10);
        Serial.println("\tHumidity is " + String(humid) + "%");

        last_millis = current_time;
    }
}

void KMM_RS0102::printStatus()
{
	Serial.print(F("temp (c) = "));
	Serial.println(this->celcius);
	Serial.print(F("humid (%) = "));
	Serial.println(this->humid);
}
double KMM_RS0102::getTemperature()
{
    return celcius;
}
double KMM_RS0102::getHumidity()
{
    return humid;
}