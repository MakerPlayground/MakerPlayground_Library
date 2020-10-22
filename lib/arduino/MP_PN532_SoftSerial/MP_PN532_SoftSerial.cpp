#include "MP_PN532_SoftSerial.h"

MP_PN532_SoftSerial::MP_PN532_SoftSerial(uint8_t nfc_tx, uint8_t nfc_rx)
	: SWSerial(nfc_tx, nfc_rx)
	, pn532swhsu(SWSerial)
	, nfc(pn532swhsu)
{
}

int MP_PN532_SoftSerial::init()
{
	nfc.begin();
	return MP_ERR_OK;
}

void MP_PN532_SoftSerial::update(unsigned long current_time)
{
	if (current_time > nextReadingTime) {
		if (nfc.tagPresent()) {
			NfcTag tag = nfc.read();
			uid = tag.getUidString();
			tagType = tag.getTagType();
		} else {
			uid = "-";
			tagType = "-";
			nextReadingTime = current_time + 80;
		}
	}
}

void MP_PN532_SoftSerial::printStatus()
{
}

bool MP_PN532_SoftSerial::checkTagUid(String tagUid) {
	return uid == tagUid;
}

bool MP_PN532_SoftSerial::foundTag() {
	return uid != "-";
}

bool MP_PN532_SoftSerial::notFoundTag() {
	return uid == "-";
}

String MP_PN532_SoftSerial::getUID() {
	return uid;
}

String MP_PN532_SoftSerial::getTag_Type() {
	return tagType;
}
