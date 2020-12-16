#include "MP_LCD_RGB_BACKLIGHT.h"

#define SCREEN_WIDTH 16

MP_LCD_RGB_BACKLIGHT::MP_LCD_RGB_BACKLIGHT()
{
}

int MP_LCD_RGB_BACKLIGHT::init()
{
    lcd.begin(16, 2);
    lcd.noBlink();
    lcd.noAutoscroll();
    lcd.noCursor();
    return MP_ERR_OK;
}

void MP_LCD_RGB_BACKLIGHT::update(unsigned long current_time)
{
}

void MP_LCD_RGB_BACKLIGHT::printStatus()
{
}

// size - 1, 2, 3
// align
//     left - 0
//     center - 1
//     right - 2
// color
// - key: Blue
//     value: 0
// - key: Cyan
//     value: 1
// - key: Dark Cyan
//     value: 2
// - key: Dark Green
//     value: 3
// - key: Dark Grey
//     value: 4
// - key: Green
//     value: 5
// - key: Green Yellow
//     value: 6
// - key: Light Grey
//     value: 7
// - key: Magenta
//     value: 8
// - key: Maroon
//     value: 9
// - key: Navy
//     value: 10
// - key: Olive
//     value: 11
// - key: Orange
//     value: 12
// - key: Pink
//     value: 13
// - key: Purple
//     value: 14
// - key: White
//     value: 15
// - key: Red
//     value: 16
// - key: Yellow
//     value: 17
void MP_LCD_RGB_BACKLIGHT::showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color)
{
    uint8_t colorR = 255, colorG = 255, colorB = 255;
    // TODO: Assign color
    if      (color == 0) { colorR = 0; colorG = 0; colorB = 255; } // Blue
    else if (color == 1) {  } // Cyan
    else if (color == 2) {  } // Dark Cyan
    else if (color == 3) {  } // Dark Green
    else if (color == 4) {  } // Dark Green
    else if (color == 5) { colorR = 0; colorG = 255; colorB = 0; } // Green
    else if (color == 6) {  } // Green Yellow
    else if (color == 7) {  } // Light Grey
    else if (color == 8) {  } // Magenta
    else if (color == 9) {  } // Maroon
    else if (color == 10) {  } // Navy
    else if (color == 11) {  } // Olive
    else if (color == 12) {  } // Orange
    else if (color == 13) {  } // Pink
    else if (color == 14) {  } // Purple
    else if (color == 15) {  } // White
    else if (color == 16) { colorR = 255; colorG = 0; colorB = 0; } // Red
    else if (color == 17) {  } // Yellow

    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT)
    {
        int8_t currentX = 0;
        int8_t currentY = rowIndex;
        
        if (align == 0)  //left
        {
            currentX = 0;
        }
        else if (align == 1) // center
        {
            currentX = (SCREEN_WIDTH - strlen(text) - 1) / 2;
        }
        else if (align == 2) // right
        {
            currentX = SCREEN_WIDTH - strlen(text) - 1;
        }
        currentY = rowIndex;
        lcd.setCursor(currentX, currentY);
        lcd.print("                ");
        lcd.setCursor(currentX, currentY);
        lcd.print(text);
    }
}

void MP_LCD_RGB_BACKLIGHT::clearRow(uint8_t row)
{
    lcd.setCursor(0, row-1);
    lcd.print("                ");
}

void MP_LCD_RGB_BACKLIGHT::clearScreen()
{
    lcd.home();
    lcd.clear();
}