#include <wiringPi.h>
#include "keypad.h"

int rows[4] = {21, 22, 23, 24};
int cols[3] = {26, 27, 28};

char keys[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

void setupKeypad() {
    for (int i = 0; i < 4; i++) {
        pinMode(rows[i], OUTPUT);
        digitalWrite(rows[i], HIGH);
    }

    for (int i = 0; i < 3; i++) {
        pinMode(cols[i], INPUT);
        pullUpDnControl(cols[i], PUD_UP);
    }
}

char getKey() {
    for (int r = 0; r < 4; r++) {
        digitalWrite(rows[r], LOW);

        for (int c = 0; c < 3; c++) {
            if (digitalRead(cols[c]) == LOW) {
                delay(200);

                while (digitalRead(cols[c]) == LOW);

                digitalWrite(rows[r], HIGH);
                return keys[r][c];
            }
        }

        digitalWrite(rows[r], HIGH);
    }

    return '\0';
}
