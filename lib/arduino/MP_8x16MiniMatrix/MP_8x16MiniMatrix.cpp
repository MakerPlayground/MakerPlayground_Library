#include "MP_8x16MiniMatrix.h"

MP_8x16MiniMatrix::MP_8x16MiniMatrix()
{

}

int MP_8x16MiniMatrix::init()
{
    matrix.begin(0x70);  // pass in the address
    last_update = 0;
	return ERR_OK;
}

void MP_8x16MiniMatrix::update(unsigned long current_time) 
{
    if (current_time - last_update > 100)
    {
        if (showMode == MODE_TEXT)
        {
            matrix.clear();
            matrix.setCursor(textScrollCurrent, 0);
            matrix.print(valueToShow.c_str());
            matrix.writeDisplay();
            textScrollCurrent -= 1;
            if (textScrollCurrent == textScrollStop) {
                textScrollCurrent = textScrollStart;
            }
        }

        last_update = current_time;
    }
}

void MP_8x16MiniMatrix::printStatus()
{
	if (showMode == MODE_TEXT)
    {
        Serial.print(F("text = "));
        Serial.println(this->valueToShow);
    }
}

void MP_8x16MiniMatrix::showText(const char* text, uint8_t text_size, int rotation)
{
    matrix.setTextSize(text_size);
    matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix.setTextColor(LED_ON);

    if (rotation == 0) {
        matrix.setRotation(1);
    } 
    else if (rotation == 90) {
        matrix.setRotation(2);
    } 
    else if (rotation == 180) {
        matrix.setRotation(3);
    } 
    else if (rotation == 270) {
        matrix.setRotation(0);
    }

	valueToShow = String(text);
    showMode = MODE_TEXT;
    textScrollCurrent = textScrollStart = 7;
    textScrollStop = -(6 * valueToShow.length());
}

void MP_8x16MiniMatrix::clear() {
    showMode = MODE_CLEAR;
    matrix.clear();
    matrix.writeDisplay();
}