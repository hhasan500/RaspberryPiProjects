#include <wiringPi.h>
#include <iostream>
#include <string>
#include "keypad.h"
#include "lcd_display.h"

using namespace std;

const int GREEN_LED = 29;
const int RED_LED = 25;
const string PASSWORD = "1234";

int main() {
    wiringPiSetup();

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    setupKeypad();
    int lcd = setupLCD();

    if (lcd < 0) {
        cout << "LCD failed" << endl;
        return 1;
    }

    string entered = "";

    displayMessage(lcd, "Enter Password");

    while (true) {
        char key = getKey();

        if (key == '\0') continue;

        if (key == '*') {
            entered = "";
            displayMessage(lcd, "Cleared");
            delay(1000);
            displayMessage(lcd, "Enter Password");
        }

        else if (key == '#') {
            if (entered == PASSWORD) {
                displayMessage(lcd, "Access Granted");
                digitalWrite(GREEN_LED, HIGH);
                delay(3000);
                digitalWrite(GREEN_LED, LOW);
            } else {
                displayMessage(lcd, "Access Denied");
                digitalWrite(RED_LED, HIGH);
                delay(3000);
                digitalWrite(RED_LED, LOW);
            }

            entered = "";
            displayMessage(lcd, "Enter Password");
        }

        else {
            entered += key;
            displayStars(lcd, entered.length());
        }
    }

    return 0;
}
