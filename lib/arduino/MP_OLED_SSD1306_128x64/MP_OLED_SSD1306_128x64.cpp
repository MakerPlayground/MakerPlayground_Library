#include "MP_OLED_SSD1306_128x64.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

MP_OLED_SSD1306_128x64::MP_OLED_SSD1306_128x64()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{
}

int MP_OLED_SSD1306_128x64::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        return ERR_CONNECT_DEVICE;
    }
    display.clearDisplay();
    return ERR_OK;
}

void MP_OLED_SSD1306_128x64::update(unsigned long current_time)
{
}

void MP_OLED_SSD1306_128x64::printStatus()
{
}

void MP_OLED_SSD1306_128x64::show()
{
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    int currentY = 0;
    for (int i=0; i < MAX_ENTRY_COUNT; i++) {
        if (entries[i].message[0]) {
            display.setTextColor(WHITE);
            display.cp437(true);
            display.setTextSize(entries[i].size);
            display.setCursor(0, currentY);
            display.print(entries[i].message);
        }
        currentY += (entries[i].size << 3);
    }
    for (int i=0; i < entryWithPositionCount; i++) {
        if (entriesWithPosition[i].message[0]) {
            display.setTextColor(WHITE);
            display.cp437(true);
            display.setTextSize(entriesWithPosition[i].size);
            display.setCursor(entriesWithPosition[i].x, entriesWithPosition[i].y);
            display.print(entriesWithPosition[i].message);
        }
    }
    display.display();
}

void MP_OLED_SSD1306_128x64::showTextAtLine(int line, char* text, char* size, char* color)
{
    int lineIndex = line - 1;
    if (lineIndex >= 0 && lineIndex < MAX_ENTRY_COUNT) {
        strcpy(entries[lineIndex].message, text);
        if (strcmp(size, "Small") == 0) {
            entries[lineIndex].size = 1;
        } else if(strcmp(size, "Medium") == 0) {
            entries[lineIndex].size = 2;
        } else if(strcmp(size, "Large") == 0) {
            entries[lineIndex].size = 3;
        } else {
            entries[lineIndex].size = 1;
        }
        show();
    }
}

void MP_OLED_SSD1306_128x64::showTextAtPosition(int x, int y, char* text, char* size, char* color)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        int storingIndex = -1;
        for(int i=0; i<entryWithPositionCount; i++) {
            if (entriesWithPosition[i].x == x && entriesWithPosition[i].y == y) {
                storingIndex = i;
                break;
            }
        }
        if (entryWithPositionCount == MAX_ENTRY_COUNT) {
            return;
        }
        if (storingIndex == -1) {
            storingIndex = entryWithPositionCount;
            entryWithPositionCount++;
        }
        strcpy(entriesWithPosition[storingIndex].message, text);
        entriesWithPosition[storingIndex].x = x;
        entriesWithPosition[storingIndex].y = y;
        if (strcmp(size, "Small") == 0) {
            entriesWithPosition[storingIndex].size = 1;
        } else if(strcmp(size, "Medium") == 0) {
            entriesWithPosition[storingIndex].size = 2;
        } else if(strcmp(size, "Large") == 0) {
            entriesWithPosition[storingIndex].size = 3;
        } else {
            entriesWithPosition[storingIndex].size = 1;
        }
        show();
    }
}

void MP_OLED_SSD1306_128x64::showNumberAtLine(int line, char* label, double value, double decimalPlaces, char* size, char* color)
{
    char* p;
    char buff[33] = "";
    char buff2[33] = "";
    char buff3[33] = "";
    strcpy(buff, label);
    if ((p = strstr(buff, "/value/")) != NULL) {
        strcpy(buff3, p+7);
        dtostrf(value, (decimalPlaces + 2), decimalPlaces, buff2);
        strcpy(p, buff2);
        strcpy(p + strlen(buff2), buff3);
    }
    showTextAtLine(line, buff, size, color);
}

void MP_OLED_SSD1306_128x64::showNumberAtPosition(int x, int y, char* label, double value, double decimalPlaces, char* size, char* color)
{
    char* p;
    char buff[33] = "";
    char buff2[33] = "";
    char buff3[33] = "";
    strcpy(buff, label);
    if ((p = strstr(buff, "/value/")) != NULL) {
        strcpy(buff3, p+7);
        dtostrf(value, (decimalPlaces + 2), decimalPlaces, buff2);
        strcpy(p, buff2);
        strcpy(p + strlen(buff2), buff3);
    }
    showTextAtPosition(x, y, buff, size, color);
}

void MP_OLED_SSD1306_128x64::clearLine(int line)
{
    strcpy(entries[line-1].message, "");
}

void MP_OLED_SSD1306_128x64::clearScreen()
{
    for (int i=0; i<MAX_ENTRY_COUNT; i++) {
        strcpy(entries[i].message, "");
        entries[i].size = 1;
    }
    for (int i=0; i<entryWithPositionCount; i++) {
        strcpy(entriesWithPosition[i].message, "");
        entriesWithPosition[i].size = 1;
        entriesWithPosition[i].x = -1;
        entriesWithPosition[i].y = -1;
    }
    entryWithPositionCount = 0;
    display.clearDisplay();
}