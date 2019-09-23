#ifndef KMM_RS0102_H
#define KMM_RS0102_H

#include "MP_DEVICE.h"
#include "ModbusMaster.h"

class KMM_RS0102
{
public:
	KMM_RS0102(uint8_t device_id);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getTemperature();
	double getHumidity();

private:
    ModbusMaster node;
	uint8_t device_id = 1;
    uint8_t result = 0;
    uint16_t data = 999;
	double celcius = 0.0;
	double humid = 0.0;
	unsigned long last_millis = 0;
};

#endif
