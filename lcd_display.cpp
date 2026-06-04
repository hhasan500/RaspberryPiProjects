#include <wiringPi.h>
#include <lcd.h>
#include <string>
#include "lcd_display.h"

using namespace std;

int setupLCD() {
    return lcdInit(
        2, 16,
        4,
        0, 1,
        2, 3, 4, 5,
        0, 0, 0, 0
    );
}

void displayMessage(int lcd, string message) {
    lcdClear(lcd);
    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, message.c_str());
}

void displayStars(int lcd, int count) {
    lcdClear(lcd);

    for (int i = 0; i < count; i++) {
        lcdPutchar(lcd, '*');
    }
}
