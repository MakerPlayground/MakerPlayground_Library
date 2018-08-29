#include "MP_TMP1637_DISPLAY.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_DHT11::ERRORS = errors_p;

MP_TMP1637_DISPLAY::MP_TMP1637_DISPLAY(uint8_t clk, uint8_t dio, const String &tag)
	:display(TM1637Dislay(clk, dio))
	,data(0)
	,brightness(7)
{
}

int MP_TMP1637_DISPLAY::init()
{
	return 0;
}

void MP_TMP1637_DISPLAY::update(unsigned long current_time)
{

}

void MP_TMP1637_DISPLAY::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->data);

	Serial.print(F("brightness = "));
	Serial.println(this->brightness);
}

void MP_TMP1637_DISPLAY::showValue(double value)
{
	data = value;
	display.setBrightness(brightness, true);
	display.showFloat(value);
}

void MP_TMP1637_DISPLAY::showData(double value)
{
	data = value;
	display.setBrightness(brightness,true);
	display.showNumberDec((int) value);
}

void MP_TMP1637_DISPLAY::setBrightness(char c[])
{
	brightness = (uint8_t) (c[0] - '0');
	display.setBrightness(brightness, true);
	display.showNumberDec((int) data);
}

void MP_TMP1637_DISPLAY::off()
{
	uint8_t data[] = {0x0, 0x0, 0x0, 0x0};
	display.setBrightness(brightness, false);
	display.setSegments(data);
}
