#include "MP_TFT_ST7789_YAHBOOM_K210.h"

#include <gfxfont.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>

#define SCREEN_WIDTH 320 // OLED display width, in pixels
#define SCREEN_HEIGHT 240 // OLED display height, in pixels

const uint8_t CHAR_WIDTH[] = {11, 14, 21};
const uint8_t CHAR_HEIGHT[] = {12, 16, 21};
const uint8_t ROW_HEIGHT[] = {15, 21, 29};
const GFXfont* FONT[] = {&FreeMono9pt7b, &FreeMono12pt7b, &FreeMono18pt7b};

MP_TFT_ST7789_YAHBOOM_K210::MP_TFT_ST7789_YAHBOOM_K210()
    : spi(SPI0)
    , lcd(SCREEN_WIDTH, SCREEN_HEIGHT, spi)
{
}

int MP_TFT_ST7789_YAHBOOM_K210::init()
{
    lcd.begin(15000000, COLOR_RED);
    lcd.setTextWrap(false);
    clearScreen();
    return MP_ERR_OK;
}

void MP_TFT_ST7789_YAHBOOM_K210::update(unsigned long current_time)
{
}

void MP_TFT_ST7789_YAHBOOM_K210::printStatus()
{
}

void MP_TFT_ST7789_YAHBOOM_K210::showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color)
{
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT)
    {
        int currentX = 0;
        if (align == 1) // align center
        {
            currentX = (SCREEN_WIDTH - (CHAR_WIDTH[size-1] * strlen(text))) / 2;
        }
        else if (align == 2) // align right
        {
            currentX = SCREEN_WIDTH - (CHAR_WIDTH[size-1] * strlen(text));
        }
        int currentY = getRowStartY(rowIndex);

        lcd.setTextSize(1);
        lcd.setFont(FONT[size - 1]);
        lcd.setCursor(currentX, currentY + CHAR_HEIGHT[size - 1] - 1);

        uint8_t oldRowHeight = row_heights[rowIndex];
        row_heights[rowIndex] = ROW_HEIGHT[size - 1];
        uint8_t heightToClear = (row_heights[rowIndex] > oldRowHeight) ? row_heights[rowIndex] : oldRowHeight;
        lcd.fillRect(0, currentY, SCREEN_WIDTH, heightToClear, COLOR_BLACK);

        lcd.setTextColor(getColorFromColorName(color));
        lcd.print(text);
    }
}

void MP_TFT_ST7789_YAHBOOM_K210::showImage(MP_IMAGE image)
{
    if (image.data != NULL && image.format == MP_IMAGE_FORMAT_RGB565
            && image.width == SCREEN_WIDTH && image.height == SCREEN_HEIGHT) {
        lcd.drawImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (uint16_t*) image.data);
    }
}

void MP_TFT_ST7789_YAHBOOM_K210::clearRow(uint8_t row)
{
    lcd.fillRect(0, getRowStartY(row - 1), SCREEN_WIDTH, row_heights[row-1], COLOR_BLACK);
    row_heights[row-1] = ROW_HEIGHT[0];
}

void MP_TFT_ST7789_YAHBOOM_K210::clearScreen()
{
    lcd.fillScreen(COLOR_BLACK);
    initRowHeights();
}

void MP_TFT_ST7789_YAHBOOM_K210::initRowHeights()
{
    for (uint8_t i=0; i<MAX_ENTRY_COUNT; i++)
    {
        row_heights[i] = ROW_HEIGHT[0];
    }
}

uint16_t MP_TFT_ST7789_YAHBOOM_K210::getColorFromColorName(uint8_t color)
{
    if (color > 17) return COLOR_WHITE;
    const uint16_t colors[] = {
        COLOR_BLUE,         /* 0 */
        COLOR_CYAN,
        COLOR_DARKCYAN,
        COLOR_DARKGREEN,
        COLOR_DARKGREY,
        COLOR_GREEN,        /* 5 */
        COLOR_GREENYELLOW,
        COLOR_LIGHTGREY,
        COLOR_MAGENTA,
        COLOR_MAROON,
        COLOR_NAVY,         /* 10 */
        COLOR_OLIVE,
        COLOR_ORANGE,
        COLOR_PINK,
        COLOR_PURPLE,
        COLOR_WHITE,        /* 15 */
        COLOR_RED,
        COLOR_YELLOW
    };
    return colors[color];
}

uint16_t MP_TFT_ST7789_YAHBOOM_K210::getRowStartY(uint8_t rowIndex)
{
    uint16_t tmp = 0;
    for (int i=0; i<rowIndex; i++)
    {
        tmp += row_heights[i];
    }
    return tmp;
}