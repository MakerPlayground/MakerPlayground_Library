#ifndef KMM_RS0401_H
#define KMM_RS0401_H

#include "MP_DEVICE.h"
#include "ModbusMaster.h"

class KMM_RS0401
{
public:
	KMM_RS0401(uint8_t device_id);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getIntensity();

private:
    ModbusMaster node;
	uint8_t device_id = 1;
    uint8_t result = 0;
    uint16_t data = 0;
	double light = 0.0;
	unsigned long last_millis = 0;
};

#endif
