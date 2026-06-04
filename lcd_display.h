#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <string>
using namespace std;

int setupLCD();
void displayMessage(int lcd, string message);
void displayStars(int lcd, int count);

#endif
