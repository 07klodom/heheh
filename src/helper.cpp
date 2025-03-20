#include <Arduino.h>

struct db
{
    bool vorher, out, in, inv;
    unsigned long last = 0;
    uint8_t taster = 0;
    uint8_t db_zeit = 0;

    void init(uint8_t _taster, uint8_t _db_zeit, bool _inv)
    {
        taster = _taster;
        db_zeit = _db_zeit;
        inv = _inv;
        pinMode(taster, INPUT);
    }
    void poll()
    {
        in = digitalRead(taster) ^ inv;
        if (millis() - last > db_zeit)
        {
            out = in;
            last = millis();
        }
    }
};
struct flanke
{
    bool vorher, pos, neg;
    bool *input;

    void init(bool *_input)
    {
        input = _input;
        vorher = *input;
    }

    void poll()
    {
        pos = !vorher && *input;
        neg = vorher && !*input;
        vorher = *input;
    }
};
struct Blinker
{
    unsigned long last = 0;
    bool state = false;

    void poll(bool enable, unsigned long blinktime, uint8_t led1, uint8_t led2)
    {
        if (!enable)
        {
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            return;
        }

        if (enable)
        {
            state = !state;
            if (millis() - last > blinktime)
            {
                digitalWrite(led1, state);
                digitalWrite(led2, !state);
            }
            last = millis();
        }
    }
};
struct LongPress
{
    unsigned long edgetime = 0;

    bool poll(bool in, uint16_t presstime)
    {
        if (in)
        {
            edgetime = millis();
            return false;
        }
        return (millis() - edgetime > presstime);
    }
};