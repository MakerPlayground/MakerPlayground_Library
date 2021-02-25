#include "MP_RC522_I2C.h"

#define REFRESH_INTERVAL 200

MP_RC522_I2C::MP_RC522_I2C(uint8_t rst_pin)
	: rst_pin(rst_pin)
    , mfrc522(0x28, rst_pin)
{
}

int MP_RC522_I2C::init() {
    mfrc522.PCD_Init();
    
    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    if ((v == 0x00) || (v == 0xFF)) {
        return MP_ERR_CONNECT_DEVICE;
    }
    if (v == 0x91) {
        version = String("v1.0");
    } else if (v == 0x92) {
        version = String("v2.0");
    }
    return MP_ERR_OK;
}

void MP_RC522_I2C::update(unsigned long current_time) {
    if (lastReadMillis < current_time + REFRESH_INTERVAL) {
        // reset uid to be empty string
        uid.remove(0);
        if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial() ) {
            return;
        }
        // make uid string
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            if (mfrc522.uid.uidByte[i] < 0x10) {
                uid += String("0");
            }
            uid += String(mfrc522.uid.uidByte[i], HEX);
            uid += String(" ");
        }
        // remove the last space
        uid.trim();
        lastReadMillis = current_time;
    }
}

void MP_RC522_I2C::printStatus() {

}

String MP_RC522_I2C::getUID() {
	return uid;
}

String MP_RC522_I2C::getReader_Version() {
    return version;
}

bool MP_RC522_I2C::checkTagUid(String tagUid) {
	return uid == tagUid;
}

bool MP_RC522_I2C::foundTag() {
	return uid != "-";
}

bool MP_RC522_I2C::notFoundTag() {
	return uid == "-";
}