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
        else if (showMode == MODE_BITMAP)
        {
            matrix.clear();
            matrix.drawBitmap(0, 0, bmp, 16, 8, LED_ON);
            matrix.writeDisplay();
        }
        last_update = current_time;
    }
}

void MP_8x16MiniMatrix::printStatus()
{
    if (showMode == MODE_TEXT) {
        Serial.print(F("text = "));
        Serial.println(this->valueToShow);
    } else if (showMode == MODE_CLEAR) {
        Serial.print(F("bitmap from "));
        Serial.println(this->valueToShow);
    } else if (showMode == MODE_CLEAR) {
        Serial.println(F("clear"));
    }
}

void MP_8x16MiniMatrix::showBitmap(const char* base16) {
    valueToShow = String(base16);
    showMode = MODE_BITMAP;
    bool tiktok = false;
    matrix.setRotation(1);

    const char* ptr = base16;
    int column_count = 0;
    int line_count = 0;
    int i = 0;
    while (ptr != '\0' && i < 16) {
        
        /* clip if the data row exceeds the dotmatrix row */
        if (line_count >= 8) {
            break;
        }

        /* clip if the data column exceeds the dotmatrix column */
        if (column_count == 16) {
            while (*ptr != '&' && *ptr != '\0') {
                ptr++;
            }
        }
        
        if (*ptr == '&' || *ptr == '\0') {
            while (column_count < 16) {
                bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000000;
                column_count += 4;
                i = tiktok ? (i+1) : i;
                tiktok = !tiktok;
            }
            line_count++;
            ptr++;
            column_count = 0;
            continue;
        }

        if (*ptr == '0') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000000;
            column_count += 4;
        }
        else if (*ptr == '1') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000001;
            column_count += 4;
        }
        else if (*ptr == '2') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000010;
            column_count += 4;
        }
        else if (*ptr == '3') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000011;
            column_count += 4;
        }
        else if (*ptr == '4') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000100;
            column_count += 4;
        }
        else if (*ptr == '5') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000101;
            column_count += 4;
        }
        else if (*ptr == '6') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000110;
            column_count += 4;
        }
        else if (*ptr == '7') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00000111;
            column_count += 4;
        }
        else if (*ptr == '8') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001000;
            column_count += 4;
        }
        else if (*ptr == '9') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001001;
            column_count += 4;
        }
        else if (*ptr == 'A') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001010;
            column_count += 4;
        }
        else if (*ptr == 'B') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001011;
            column_count += 4;
        }
        else if (*ptr == 'C') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001100;
            column_count += 4;
        }
        else if (*ptr == 'D') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001101;
            column_count += 4;
        }
        else if (*ptr == 'E') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001110;
            column_count += 4;
        }
        else if (*ptr == 'F') {
            bmp[i] = (tiktok ? bmp[i] << 4 : 0) | 0B00001111;
            column_count += 4;
        }

        ptr++;
        i = tiktok ? (i+1) : i;
        tiktok = !tiktok;
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