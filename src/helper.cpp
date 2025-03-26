#include "helper.h"

// ****************************************************************************
// ************************** button ******************************************
// ****************************************************************************

void button::init(uint8_t _pinNr, bool _neg, uint8_t _debounce_time, uint16_t _longpress_time)
{
    analogblinker test;
    pinNr = _pinNr;
    neg = _neg;
    debounce_time = _debounce_time;
    longpress_time = _longpress_time;

    pinMode(pinNr, INPUT);
    debounced = db_last = last = digitalRead(pinNr); // ..damit nicht schon beim Start eine Flanke ausgelöst wird..
}

void button::poll()
{
    in = digitalRead(pinNr);
    in = neg ? !in : in;
    debounce();
    check_edge();
    check_longpress();
}

void button::debounce()
{
    if (millis() - lasttime > debounce_time)
    {
        if (in != db_last)
        {
            debounced = db_last;
        }
        else
        {
            debounced = in;
        }
        lasttime = millis();
        db_last = in;
    }
}

void button::check_edge()
{
    rising = false;

    if (debounced && !last)
        rising = true;

    falling = false;

    if (!debounced && last)
        falling = true;

    last = debounced;
}


void button::check_longpress()
{
    longpress = false;

    if (rising)
    {
        last_rising = millis();
        return;
    }

    if (falling)
    {
        if (millis() - last_rising > longpress_time)
        {
            longpress = true;
        }
    }
    else // damit longpress nur einen einzigen Zyklus lang true ist
    {
        longpress = false;
    }
}

// ****************************************************************************
// ************************** blinker *****************************************
// ****************************************************************************

void blinker::init(uint8_t _pin1, bool _neg1, uint8_t _pin2, bool _neg2, uint16_t _blinkTime, bool _enable)
{
    pin1 = _pin1;
    neg1 = _neg1;
    pin2 = _pin2;
    neg2 = _neg2;
    blinkTime = _blinkTime;
    enable = _enable;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

void blinker::poll()
{
    if (!enable)
    {
        digitalWrite(pin1, neg1 ? HIGH : LOW);
        digitalWrite(pin2, neg2 ? HIGH : LOW);
        return;
    }
    else if (millis() - lastblink > blinkTime)
    {
        // Serial.println(".");
        digitalWrite(pin1, neg1 ? !blinkState : blinkState);
        digitalWrite(pin2, neg1 ? !blinkState : blinkState);
        blinkState = !blinkState;
        lastblink = millis();
    }
}

void blinker::on() { enable = true; }   // setter-Methode zum Einschalten des Blinkers
void blinker::off() { enable = false; } // setter-Methode zum Ausschalten des Blinkers

