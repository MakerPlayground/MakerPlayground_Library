#include "MP_TFT_M5Stack.h"

#define SCREEN_WIDTH 320 // OLED display width, in pixels
#define SCREEN_HEIGHT 240 // OLED display height, in pixels

#define CHAR_WIDTH_1X 11
#define CHAR_HEIGHT_1X 13

#define ROW_HEIGHT 13

// #define UPDATE_INTERVAL 500

MP_TFT_M5Stack::MP_TFT_M5Stack()
{
}

int MP_TFT_M5Stack::init()
{
    display.begin();
    display.setTextWrap(false);
    clearScreen();
    return ERR_OK;
}

void MP_TFT_M5Stack::update(unsigned long current_time)
{
}

void MP_TFT_M5Stack::printStatus()
{
}

void MP_TFT_M5Stack::showTextAtRow(uint8_t row, const char* text, const char* size, const char* align, const char* color) {
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT)
    {
        int currentX = 0;
        int currentY = 0;
        uint8_t sizeInt = (strcmp(size, "1x") == 0) ? 1 : ((strcmp(size, "2x") == 0) ? 2 : ((strcmp(size, "3x") == 0) ? 3 : 1));
        
        if (strcmp(align, "Left") == 0)
        {
            currentX = 0;
        }
        else if (strcmp(align, "Center") == 0)
        {
            currentX = (SCREEN_WIDTH - (CHAR_WIDTH_1X * sizeInt * strlen(text))) / 2;
        }
        else if (strcmp(align, "Right") == 0)
        {
            currentX = SCREEN_WIDTH - (CHAR_WIDTH_1X * sizeInt * strlen(text));
        }
        currentY = rowIndex * ROW_HEIGHT;

        display.fillRect(0, rowIndex * ROW_HEIGHT + 1, SCREEN_WIDTH, (sizeInt > row_heights[rowIndex] ? sizeInt : row_heights[rowIndex]) * ROW_HEIGHT, BLACK);
        row_heights[rowIndex] = sizeInt;

        if (strcmp(size, "1x") == 0) {
            display.setTextSize(1);
            display.setFreeFont(&FreeMonoBold9pt7b);
        } else if(strcmp(size, "2x") == 0) {
            display.setTextSize(1);
            display.setFreeFont(&FreeMonoBold18pt7b);
        } else if(strcmp(size, "3x") == 0) {
            display.setTextSize(3);
            display.setFreeFont(&FreeMonoBold9pt7b);
        }
        display.setTextColor(getColorFromColorName(color));
        display.setCursor(currentX, currentY + row_heights[rowIndex] * (ROW_HEIGHT - 1));
        display.print(text);
        display.display();
    }
}

void MP_TFT_M5Stack::clearRow(uint8_t row) {
    display.fillRect(0, (row-1) * ROW_HEIGHT, SCREEN_WIDTH, row_heights[row-1] * ROW_HEIGHT, BLACK);
    display.display();
    row_heights[row-1] = 1;
}

void MP_TFT_M5Stack::clearScreen() {
    display.clearDisplay();
    display.display();
    initRowHeights();
}

const GFXfont * MP_TFT_M5Stack::getFontFromSizeName(const char* size)
{
    if (strcmp(size, "1x") == 0) {
        return &FreeMonoBold9pt7b;
    } else if(strcmp(size, "2x") == 0) {
        return &FreeMonoBold18pt7b;
    } else if(strcmp(size, "3x") == 0) {
        return &FreeMonoBold18pt7b;
    }
    return &FreeMonoBold9pt7b;
}

uint16_t MP_TFT_M5Stack::getColorFromColorName(const char* color)
{
    if (strcmp(color, "Navy") == 0) {
        return TFT_NAVY;
    } else if (strcmp(color, "Dark Green") == 0) {
        return TFT_DARKGREEN;
    } else if (strcmp(color, "Dark Cyan") == 0) {
        return TFT_DARKCYAN;
    } else if (strcmp(color, "Maroon") == 0) {
        return TFT_MAROON;
    } else if (strcmp(color, "Purple") == 0) {
        return TFT_PURPLE;
    } else if (strcmp(color, "Olive") == 0) {
        return TFT_OLIVE;
    } else if (strcmp(color, "Light Grey") == 0) {
        return TFT_LIGHTGREY;
    } else if (strcmp(color, "Dark Grey") == 0) {
        return TFT_DARKGREY;
    } else if (strcmp(color, "Blue") == 0) {
        return TFT_BLUE;
    } else if (strcmp(color, "Green") == 0) {
        return TFT_GREEN;
    } else if (strcmp(color, "Cyan") == 0) {
        return TFT_CYAN;
    } else if (strcmp(color, "Red") == 0) {
        return TFT_RED;
    } else if (strcmp(color, "Magenta") == 0) {
        return TFT_MAGENTA;
    } else if (strcmp(color, "Yellow") == 0) {
        return TFT_YELLOW;
    } else if (strcmp(color, "White") == 0) {
        return TFT_WHITE;
    } else if (strcmp(color, "Orange") == 0) {
        return TFT_ORANGE;
    } else if (strcmp(color, "Green Yellow") == 0) {
        return TFT_GREENYELLOW;
    } else if (strcmp(color, "Pink") == 0) {
        return TFT_PINK;
    }
    return TFT_WHITE;
}

void MP_TFT_M5Stack::initRowHeights()
{
    for (uint8_t i=0; i<MAX_ENTRY_COUNT; i++)
    {
        row_heights[i] = 1;
    }
}