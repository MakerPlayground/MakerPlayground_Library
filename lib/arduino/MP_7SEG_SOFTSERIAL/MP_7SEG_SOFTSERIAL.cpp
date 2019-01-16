#include "MP_7SEG_SOFTSERIAL.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_7SEG_SOFTSERIAL::ERRORS = errors_p;

uint8_t digits[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

MP_7SEG_SOFTSERIAL::MP_7SEG_SOFTSERIAL(uint8_t tx)
#if defined(ARDUINO_ARCH_AVR)
	:serial(SendOnlySoftwareSerial(tx))
#elif defined(ARDUINO_ARCH_ESP8266)
	:serial(SoftwareSerial(-1, tx))
#endif
{
}

int MP_7SEG_SOFTSERIAL::init()
{
	serial.begin(9600);
	return 0;
}

void MP_7SEG_SOFTSERIAL::update(unsigned long current_time) 
{
	
}

void MP_7SEG_SOFTSERIAL::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->valueToShow);
}

void MP_7SEG_SOFTSERIAL::showTwoIntWithColon(int8_t beforeColon, int8_t afterColon) {
	valueToShow = String(beforeColon) + String(":") + String(afterColon);

	serial.write((byte)0x7f);
	serial.write((byte)3);
	if (beforeColon < 0 && beforeColon > -10) {
		serial.write((byte)0b01000000);
		serial.write(digits[-beforeColon]);
	} else if (beforeColon >= 0 && beforeColon < 100) {
		serial.write(digits[beforeColon / 10]);
		serial.write(digits[beforeColon % 10]);
	} else {
		serial.write((byte)0b01000000);
		serial.write((byte)0b01000000);
	}

	if (afterColon < 0 && afterColon > -10) {
		serial.write((byte)0b01000000);
		serial.write(digits[-afterColon]);
	} else if (afterColon >= 0 && afterColon < 100) {
		serial.write(digits[afterColon / 10]);
		serial.write(digits[afterColon % 10]);
	} else {
		serial.write((byte)0b01000000);
		serial.write((byte)0b01000000);
	}
	serial.write((byte)0b00000011);
	serial.write((byte)'\r');
	serial.write((byte)'\n');
}

void MP_7SEG_SOFTSERIAL::showData(double value)
{
	valueToShow = String(value);
	showFloat(value);
}

void MP_7SEG_SOFTSERIAL::off()
{
	serial.write((byte)0x7f);
	serial.write((byte)3);
	serial.write((byte)0b00000000);
	serial.write((byte)0b00000000);
	serial.write((byte)0b00000000);
	serial.write((byte)0b00000000);
	serial.write((byte)0b00000000);
	serial.write((byte)'\r');
	serial.write((byte)'\n');
}


void MP_7SEG_SOFTSERIAL::sendInvalid()
{
	serial.write((byte)0x7f);
	serial.write((byte)3);
	serial.write((byte)0b01000000);
	serial.write((byte)0b01000000);
	serial.write((byte)0b01000000);
	serial.write((byte)0b01000000);
	serial.write((byte)0b00000000);
	serial.write((byte)'\r');
	serial.write((byte)'\n');
}

void MP_7SEG_SOFTSERIAL::showFloat(double num)
{
	if (num >= 0) {
		if (num < 10) {
			sendData(num * 1000, 0x08, false);
		} else if (num < 100) {
			sendData(num * 100, 0x04, false);
		} else if (num < 1000) {
			sendData(num * 10, 0x02, false);
		} else if (num < 10000) {
			sendData(num, 0x00, false);
		} else {
			sendInvalid();
		}
	} else {
		num = -num;
		if (num < 10) {
			sendData(num * 100, 0x04, true);
		} else if (num < 100) {
			sendData(num * 10, 0x02, true);
		} else if (num < 1000) {
			sendData(num, 0x00, true);
		} else {
			sendInvalid();
		}
	}
}

void MP_7SEG_SOFTSERIAL::sendData(int num, uint8_t dot, bool negative)
{
	// split digit
	uint8_t tmp[4];
	for (int i=0; i<4; i++)
	{
		tmp[i] = num % 10;
		num = num / 10;
	}

	// send
	serial.write((byte)0x7f);
	serial.write((byte)3);
	if (negative) {
		serial.write((byte)0b01000000);
		for (int i=2; i>=0; i--) 
		{
			if (dot & (1 << i))
				serial.write((byte)(digits[tmp[i]] | 0b10000000));
			else
				serial.write((byte)(digits[tmp[i]]));
		}
	} else {
		for (int i=3; i>=0; i--) 
		{
			if (dot & (1 << i))
				serial.write((byte)(digits[tmp[i]] | 0b10000000));
			else
				serial.write((byte)(digits[tmp[i]]));
		}
	}
	serial.write((byte)0);
	serial.write((byte)'\r');
	serial.write((byte)'\n');
}
