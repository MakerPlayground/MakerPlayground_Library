#include "MP_OLED_SSD1306_128x64.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define CHAR_WIDTH_1X 6
#define CHAR_HEIGHT_1X 8

#define ROW_HEIGHT 8

MP_OLED_SSD1306_128x64::MP_OLED_SSD1306_128x64()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire)
{
}

int MP_OLED_SSD1306_128x64::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        return ERR_CONNECT_DEVICE;
    }
    display.clearDisplay();
    display.display();
    display.setTextWrap(false);
    display.setTextColor(WHITE);
    display.cp437();
    initRowHeights();
    return ERR_OK;
}

void MP_OLED_SSD1306_128x64::update(unsigned long current_time)
{
}

void MP_OLED_SSD1306_128x64::printStatus()
{
}

void MP_OLED_SSD1306_128x64::showTextAtRow(uint8_t row, const char* text, const char* size, const char* align, const char* color)
{
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT)
    {
        int8_t currentX = 0;
        int8_t currentY = 0;
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
        
        display.fillRect(0, rowIndex * ROW_HEIGHT, SCREEN_WIDTH, (sizeInt > row_heights[rowIndex] ? sizeInt : row_heights[rowIndex]) * ROW_HEIGHT, BLACK);
        display.setTextSize(sizeInt);
        display.setCursor(currentX, currentY);
        display.print(text);
        display.display();
        row_heights[rowIndex] = sizeInt;
    }
}

void MP_OLED_SSD1306_128x64::clearRow(uint8_t row)
{
    display.fillRect(0, (row-1) * ROW_HEIGHT, SCREEN_WIDTH, row_heights[row-1] * ROW_HEIGHT, BLACK);
    display.display();
    row_heights[row-1] = 1;
}

void MP_OLED_SSD1306_128x64::clearScreen()
{
    display.clearDisplay();
    display.display();
    initRowHeights();
}

void MP_OLED_SSD1306_128x64::initRowHeights()
{
    for (uint8_t i=0; i<MAX_ENTRY_COUNT; i++)
    {
        row_heights[i] = 1;
    }
}