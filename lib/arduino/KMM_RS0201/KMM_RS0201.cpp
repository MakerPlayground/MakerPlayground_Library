#include "KMM_RS0201.h"

KMM_RS0201::KMM_RS0201(uint8_t device_id)
	:device_id(device_id)
{
}

int KMM_RS0201::init()
{
	return ERR_OK;
}

void KMM_RS0201::update(unsigned long current_time)
{
    if (current_time - last_millis > 200)
    {
        node.begin(device_id, Serial);
        // Reading sensor modbus device, RS1-0201
        result = node.readHoldingRegisters(0x0000,2);
        data = node.getResponseBuffer(0x00);
        value = map(data,120,1012,100,0);
        last_millis = current_time;
        Serial.print("device_id = ");
        Serial.println(this->device_id);
        Serial.print("result = ");
        Serial.println(this->result);
        Serial.print("data = ");
        Serial.println(this->data);
        Serial.print("value = ");
        Serial.println(this->value);
    }
}

void KMM_RS0201::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double KMM_RS0201::getPercent()
{
	return value;
}
