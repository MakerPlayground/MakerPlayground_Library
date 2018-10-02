#include "MP_BUZZER_ESP32.h"

const uint8_t ledcChannel = 0;	// (0-15)

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BUZZER_ESP32::ERRORS = errors_p;

MP_BUZZER_ESP32::MP_BUZZER_ESP32(uint8_t pin)
	:pin(pin)
	,playing(false)
	,currentTime(0)
	,endTime(0)
{
}

int MP_BUZZER_ESP32::init()
{
	ledcAttachPin(pin, ledcChannel);
	ledcSetup(ledcChannel, 440, 10);	// 440 is choose arbitrarily (any value should work)	
										// use 10 bits as ledcWriteTone uses 10 bit precision internally
										// we may not needed this function but we included it for completeness
	return 0;
}

void MP_BUZZER_ESP32::update(unsigned long currentTime) 
{
	// this->currentTime = currentTime;
	if (playing && (currentTime > endTime)) {
		ledcWriteTone(ledcChannel, 0);
		playing = false;
	}
}

void MP_BUZZER_ESP32::printStatus() {
	Serial.print(F("If this device is not work properly, check the connection on pin "));
	Serial.println(this->pin);
}

void MP_BUZZER_ESP32::beep()
{
	ledcWriteTone(ledcChannel, 2000);
	endTime = millis() + 100;
	playing = true;
}

void MP_BUZZER_ESP32::play(double frequency, double duration)
{
	ledcWriteTone(ledcChannel, frequency);
	endTime = millis() + (duration * 1000);
	playing = true;
}