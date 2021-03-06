#ifndef KMM_RS0201_H
#define KMM_RS0201_H

#include "MP_DEVICE.h"
#include "ModbusMaster.h"

class KMM_RS0201
{
public:
	KMM_RS0201(uint8_t device_id);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getPercent();

private:
    ModbusMaster node;
	uint8_t device_id = 1;
    uint8_t result = 0;
    uint16_t data = 0;
	double value = 0.0;
	unsigned long last_millis = 0;
};

#endif
