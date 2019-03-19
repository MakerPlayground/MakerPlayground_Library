#include "MP_TM1637_DISPLAY.h"

MP_TM1637_DISPLAY::MP_TM1637_DISPLAY(uint8_t clk, uint8_t dio)
	:display(TM1637Display(clk, dio))
	,data(0)
	,brightness(7)
{
}

int MP_TM1637_DISPLAY::init()
{
	return ERR_OK;
}

void MP_TM1637_DISPLAY::update(unsigned long current_time)
{

}

void MP_TM1637_DISPLAY::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->data);

	Serial.print(F("brightness = "));
	Serial.println(this->brightness);
}

void MP_TM1637_DISPLAY::showData(double value)
{
	data = value;
	display.setBrightness(brightness,true);
	display.showNumberDec((int) value);
}

void MP_TM1637_DISPLAY::setBrightness(char c[])
{
	brightness = (uint8_t) (c[0] - '0');
	display.setBrightness(brightness, true);
	display.showNumberDec((int) data);
}

void MP_TM1637_DISPLAY::off()
{
	uint8_t data[] = {0x0, 0x0, 0x0, 0x0};
	display.setBrightness(brightness, false);
	display.setSegments(data);
}
