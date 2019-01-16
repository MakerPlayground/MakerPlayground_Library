#include "MP_OLED_SSD1306_128x64.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't detect SSD1306 OLED display. Please check connection!!!";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_OLED_SSD1306_128x64::ERRORS = errors_p;


MP_OLED_SSD1306_128x64::MP_OLED_SSD1306_128x64()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
}

int MP_OLED_SSD1306_128x64::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        return 1;
    }
    display.clearDisplay();
    return 0;
}

void MP_OLED_SSD1306_128x64::update(unsigned long current_time)
{
}

void MP_OLED_SSD1306_128x64::printStatus()
{
}

void MP_OLED_SSD1306_128x64::showText(int line, char* text)
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, (line - 1) * 8);
    display.cp437(true);
    display.fillRect(0, (line - 1) * 8, SCREEN_WIDTH, 8, BLACK);
    display.print(text);
    display.display();
}

void MP_OLED_SSD1306_128x64::showNumber(int line, char* label, double value)
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, (line - 1) * 8);
    display.cp437(true);
    display.fillRect(0, (line - 1) * 8, SCREEN_WIDTH, 8, BLACK);

    String tmp(label);
    tmp.replace("/value/", String(value));

    display.print(tmp);
    display.display();
}

void MP_OLED_SSD1306_128x64::clearScreen()
{
    display.clearDisplay();
}