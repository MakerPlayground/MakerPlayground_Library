#include "MP_TMP1637_DISPLAY.h"

MP_TMP1637_DISPLAY::MP_TMP1637_DISPLAY(uint8_t clk, uint8_t dio, const String &tag)
	:display(TM1637Dislay(clk, dio))
	,data(0)
	,brightness(7)
	,tag(tag)
{
}

void MP_TMP1637_DISPLAY::init()
{
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
	brightness = (int) c[0] - '0';
	display.setBrightness(brightness, true);
	display.showNumberDec((int) data);
}

void MP_TMP1637_DISPLAY::off()
{
	uint8_t data[] = {0x0, 0x0, 0x0, 0x0};
	display.setBrightness(brightness, false);
	display.setSegments(data);
}
