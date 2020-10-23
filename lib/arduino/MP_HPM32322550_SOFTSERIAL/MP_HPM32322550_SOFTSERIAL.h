#ifndef MP_HPM32322550_SOFTSERIAL_H
#define MP_HPM32322550_SOFTSERIAL_H

#include "MP_DEVICE.h"
#include <pm25.h>
#include <SoftwareSerial.h>

class MP_HPM32322550_SOFTSERIAL
{
public:
	MP_HPM32322550_SOFTSERIAL(uint8_t dust_tx, uint8_t dust_rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	uint16_t getAtmospheric_PM_2_5();
	uint16_t getAtmospheric_PM_10();

	bool isDataValid();
	bool isDataInvalid();

private:
	SoftwareSerial pm25_ser;
	unsigned long lastReadSuccess = 0;
};

#endif
