#include "MP_OLED_SSD1315_128x64.h"

#include <Arduino.h>
#include <U8g2lib.h>

#define ROW_HEIGHT 8

MP_OLED_SSD1315_128x64::MP_OLED_SSD1315_128x64()
    : u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE)
{
}

void MP_OLED_SSD1315_128x64::initCacheValues() {
    for(int i=0; i<MAX_ENTRY_COUNT; i++) {
        texts[i] = "";
        aligns[i] = 0;
        sizes[i] = 1;
    }
}

int MP_OLED_SSD1315_128x64::init()
{
    initCacheValues();
    if (!u8g2.begin()) {
        return MP_ERR_CONNECT_DEVICE;
    }
    u8g2.clear();
    return MP_ERR_OK;
}

void MP_OLED_SSD1315_128x64::update(unsigned long current_time)
{
}

void MP_OLED_SSD1315_128x64::printStatus()
{
}

// size - 1, 2, 3
// align
//     left - 0
//     center - 1
//     right - 2
// color - ignore (always white)
void MP_OLED_SSD1315_128x64::showTextAtRow(uint8_t row, const char* text, uint8_t size, uint8_t align, uint8_t color)
{
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT) {
        texts[rowIndex] = text;
        aligns[rowIndex] = align;
        sizes[rowIndex] = size;
        drawAll();
    }
}

void MP_OLED_SSD1315_128x64::drawAll() {
    uint8_t screen_width = u8g2.getDisplayWidth();
    u8g2.clear();
    u8g2.firstPage();
    do {
        u8g2.setDrawColor(1);
        for (int i=0; i<MAX_ENTRY_COUNT; i++) {
            uint8_t size = sizes[i];
            uint8_t align = aligns[i];
            const char * text = texts[i].c_str();
            int8_t currentX = 0;
            int8_t currentY = 0;

            // set font
            if (size == 1) {
                u8g2.setFont(u8g2_font_5x8_mr);
            } else if (size == 2) {
                u8g2.setFont(u8g2_font_inb16_mr);
            } else if (size == 3) {
                u8g2.setFont(u8g2_font_inb24_mr);
            }

            // retrieve x, y
            if (align == 0) { //left
                currentX = 0;
            } else if (align == 1) { // center
                currentX = (screen_width - u8g2.getStrWidth(text)) / 2;
            } else if (align == 2) { // right
                currentX = screen_width - u8g2.getStrWidth(text);
            }
            currentY = (i+1+(size-1)) * ROW_HEIGHT;
            u8g2.drawStr(currentX, currentY, text);
        }
    } while (u8g2.nextPage());
}

void MP_OLED_SSD1315_128x64::clearRow(uint8_t row)
{
    uint8_t rowIndex = row - 1;
    if (rowIndex >= 0 && rowIndex < MAX_ENTRY_COUNT) {
        texts[rowIndex] = "";
        aligns[rowIndex] = 0;
        sizes[rowIndex] = 1;
        drawAll();
    }
}

void MP_OLED_SSD1315_128x64::clearScreen()
{
    initCacheValues();
    u8g2.clear();
    initRowHeights();
}

void MP_OLED_SSD1315_128x64::initRowHeights()
{
    for (uint8_t i=0; i<MAX_ENTRY_COUNT; i++)
    {
        sizes[i] = 1;
    }
}