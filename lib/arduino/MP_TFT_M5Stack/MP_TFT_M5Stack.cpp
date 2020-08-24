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
    return MP_ERR_OK;
}

void MP_TFT_M5Stack::update(unsigned long current_time)
{
}

void MP_TFT_M5Stack::printStatus()
{
}

void MP_TFT_M5Stack::showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color) {
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT)
    {
        int currentX = 0;
        int currentY = 0;
        
        if (align == 0) // left
        {
            currentX = 0;
        }
        else if (align == 1) // center
        {
            currentX = (SCREEN_WIDTH - (CHAR_WIDTH_1X * size * strlen(text))) / 2;
        }
        else if (align == 2) // right
        {
            currentX = SCREEN_WIDTH - (CHAR_WIDTH_1X * size * strlen(text));
        }
        currentY = rowIndex * ROW_HEIGHT;

        display.fillRect(0, rowIndex * ROW_HEIGHT + 1, SCREEN_WIDTH, (size > row_heights[rowIndex] ? size : row_heights[rowIndex]) * ROW_HEIGHT, BLACK);
        row_heights[rowIndex] = size;

        if (size == 1) {
            display.setTextSize(1);
            display.setFreeFont(&FreeMonoBold9pt7b);
        } else if(size == 2) {
            display.setTextSize(1);
            display.setFreeFont(&FreeMonoBold18pt7b);
        } else if(size == 3) {
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

uint16_t MP_TFT_M5Stack::getColorFromColorName(uint8_t color)
{
    if (color < 0 || color > 17) return TFT_WHITE;
    const uint16_t colors[] = {
        TFT_BLUE,         /* 0 */
        TFT_CYAN,
        TFT_DARKCYAN,
        TFT_DARKGREEN,
        TFT_DARKGREY,
        TFT_GREEN,        /* 5 */
        TFT_GREENYELLOW,
        TFT_LIGHTGREY,
        TFT_MAGENTA,
        TFT_MAROON,
        TFT_NAVY,         /* 10 */
        TFT_OLIVE,
        TFT_ORANGE,
        TFT_PINK,
        TFT_PURPLE,
        TFT_WHITE,        /* 15 */
        TFT_RED,
        TFT_YELLOW
    };
    return colors[color];
}

void MP_TFT_M5Stack::initRowHeights()
{
    for (uint8_t i=0; i<MAX_ENTRY_COUNT; i++)
    {
        row_heights[i] = 1;
    }
}