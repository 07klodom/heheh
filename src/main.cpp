#include <Arduino.h>
#define LED1 2
#define LED2 3
#define LED3 4
#define TASTER1 7
#define TASTER2 8
#define DB_ZEIT 50
#define PRESSTIME 1000
#define BLINKTIME 300
#define BLINKSTEP 100
bool enable = false;
#include "helper.h"
db db_taster1;
db db_taster2;

flanke fp_taster1;
flanke fp_taster2;

Blinker blinker;

LongPress longpress;

void setup()
{
    Serial.begin(57600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(TASTER1, INPUT);
    pinMode(TASTER2, INPUT);

    db_taster1.init(TASTER1, DB_ZEIT, false);
    db_taster2.init(TASTER2, DB_ZEIT, false);
    fp_taster1.init(&db_taster1.out);
    fp_taster2.init(&db_taster2.out);
}

uint8_t counter = 0;

void loop()
{
    db_taster1.poll();
    db_taster2.poll();

    fp_taster1.poll();
    fp_taster2.poll();

    if (fp_taster1.pos)
    {
        counter++;
        enable = true;
        Serial.println(counter);
    }
    else if (fp_taster2.neg)
    {
        counter--;
        enable = false;
        Serial.println(counter);
    }
}
