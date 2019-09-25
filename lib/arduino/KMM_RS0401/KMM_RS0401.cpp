#include "KMM_RS0401.h"

KMM_RS0401::KMM_RS0401(uint8_t device_id)
	:device_id(device_id)
{
}

int KMM_RS0401::init()
{
	return ERR_OK;
}

void KMM_RS0401::update(unsigned long current_time)
{
    if (current_time - last_millis > 200)
    {
        node.begin(device_id, Serial);
        
        // Reading sensor modbus device , RS1-0401 
        result = node.readHoldingRegisters(0x0000,2); 
        if (result == 0)
        {
            // Ambient light sensor is long data type. Double word size from register word 0 and 1 
            light = (double) (((unsigned long)(node.getResponseBuffer(0x00))<<16)|node.getResponseBuffer(0x01));
            Serial.print("Device ID#");
            Serial.print(device_id); 
            Serial.println("\tLight intensity is " + String(light) + "Lux");         
        }
        else
        { 
            Serial.println("No device found...   ");
        }
        last_millis = current_time;
    }
}

void KMM_RS0401::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->light);
}

double KMM_RS0401::getIntensity()
{
	return light;
}
