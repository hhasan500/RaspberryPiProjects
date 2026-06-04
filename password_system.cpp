#include <wiringPi.h>
#include <lcd.h>
#include <iostream>
#include <string>

using namespace std;

/*
Keypad Wiring

Rows:
GPIO5  -> wiringPi 21
GPIO6  -> wiringPi 22
GPIO13 -> wiringPi 23
GPIO19 -> wiringPi 24

Columns:
GPIO12 -> wiringPi 26
GPIO16 -> wiringPi 27
GPIO20 -> wiringPi 28
*/

int rows[4] = {21,22,23,24};
int cols[3] = {26,27,28};

char keypad[4][3] =
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

const int GREEN_LED = 29;   // GPIO21
const int RED_LED   = 25;   // GPIO26

string PASSWORD = "1234";

char getKey()
{
    for(int r=0; r<4; r++)
    {
        digitalWrite(rows[r], LOW);

        for(int c=0; c<3; c++)
        {
            if(digitalRead(cols[c]) == LOW)
            {
                delay(200);

                while(digitalRead(cols[c]) == LOW);

                digitalWrite(rows[r], HIGH);

                return keypad[r][c];
            }
        }

        digitalWrite(rows[r], HIGH);
    }

    return '\0';
}

int main()
{
    wiringPiSetup();

    for(int i=0;i<4;i++)
    {
        pinMode(rows[i], OUTPUT);
        digitalWrite(rows[i], HIGH);
    }

    for(int i=0;i<3;i++)
    {
        pinMode(cols[i], INPUT);
        pullUpDnControl(cols[i], PUD_UP);
    }

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    int lcdHandle = lcdInit(
        2,16,
        4,
        0,1,
        2,3,4,5,
        0,0,0,0
    );

    if(lcdHandle < 0)
    {
        cout << "LCD failed" << endl;
        return 1;
    }

    string entered = "";

    lcdClear(lcdHandle);
    lcdPosition(lcdHandle,0,0);
    lcdPuts(lcdHandle,"Enter Password");

    while(true)
    {
        char key = getKey();

        if(key == '\0')
            continue;

        if(key == '*')
        {
            entered = "";

            lcdClear(lcdHandle);
            lcdPuts(lcdHandle,"Cleared");

            delay(1000);

            lcdClear(lcdHandle);
            lcdPuts(lcdHandle,"Enter Password");
        }

        else if(key == '#')
        {
            lcdClear(lcdHandle);

            if(entered == PASSWORD)
            {
                lcdPuts(lcdHandle,"Access Granted");

                digitalWrite(GREEN_LED,HIGH);

                delay(3000);

                digitalWrite(GREEN_LED,LOW);
            }
            else
            {
                lcdPuts(lcdHandle,"Access Denied");

                digitalWrite(RED_LED,HIGH);

                delay(3000);

                digitalWrite(RED_LED,LOW);
            }

            entered = "";

            lcdClear(lcdHandle);
            lcdPuts(lcdHandle,"Enter Password");
        }

        else
        {
            entered += key;

            lcdClear(lcdHandle);

            for(size_t i=0;i<entered.length();i++)
                lcdPutchar(lcdHandle,'*');
        }
    }

    return 0;
}
