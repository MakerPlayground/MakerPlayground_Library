#ifndef MP_PN532_SoftSerial_H
#define MP_PN532_SoftSerial_H

#include "MP_DEVICE.h"

#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include <PN532/PN532_SWHSU/PN532_SWHSU.h>
#include "SoftwareSerial.h"
#include "Wire.h"
#include "SPI.h"

#undef NDEF_USE_SERIAL

class MP_PN532_SoftSerial
{
public:
	MP_PN532_SoftSerial(uint8_t rx, uint8_t tx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool checkTagUid(String tagUid);
	bool foundTag();
	bool notFoundTag();

	String getUID();
	String getTag_Type();

private:
	SoftwareSerial SWSerial;
	PN532_SWHSU pn532swhsu;
	NfcAdapter nfc;
	String uid;
	String tagType;
	unsigned long nextReadingTime = 0;
};

#endif
