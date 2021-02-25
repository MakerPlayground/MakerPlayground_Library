#ifndef MP_RC522_I2C_H
#define MP_RC522_I2C_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "MFRC522_I2C.h"

class MP_RC522_I2C
{
public:
	MP_RC522_I2C(uint8_t rst_pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    bool checkTagUid(String tagUid);
    bool foundTag();
    bool notFoundTag();

    String getUID();
    String getReader_Version();

private:
    String uid = "";
    String version = "(unknown)";
	uint8_t rst_pin;
    MFRC522 mfrc522;
    unsigned long lastReadMillis = 0;
};

#endif
