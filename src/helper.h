#ifndef helper_h
#define helper_h

#include <Arduino.h>
#include "analogblinker.h"
/*
    ----------- INFO -------------
    Diese Struktur implementiert eine Taster-Auswertung.
    Es kann eine Debounce Zeit in ms (max. 255) gesetzt werden oder das Debounce
    mit 0 deaktiviert werden.
    Die Struktur verfügt über init-Methode zum Setzen der notwendigen
    Parameter und eine poll-Methode, welche bei jedem Loop ausgeführt
    werden soll. Diese stehen als Member-Variablen zur Verfügung.
*/
struct button
{
    analogblinker test;
    // Member-Variable(n)
    bool in = false;
    bool neg = false;
    bool db_last = false;
    bool debounced = false;
    bool rising = false;
    bool falling = false;
    bool last = false;
    bool longpress = false;
    unsigned long lasttime = 0;
    unsigned long last_rising = 0;
    uint8_t pinNr = 0;
    uint8_t debounce_time = 20;
    uint16_t longpress_time = 1000;

    // Methode(n)
    // Pin-Nummer, true = negative Logik, Debounce-Zeit [ms], Zeitgrenze für langen Druck [ms]
    void init(uint8_t, bool, uint8_t, uint16_t);

    void poll();

    // wenn Debounce-Zeit = 0, dann kein Debounce
    void debounce();
    void check_edge();
    void check_longpress();
};

/*
    ----------- INFO -------------
    Dise Struktur implementiert einen Wechselblinker auf zwei bliebige Pins.
    In der init-Methode können die Pin-Nummern definiert werden. Außerdem ist es
    möglich eine negation des Ausgangs direkt anzugeben. Die poll-Methode muss
    bei jedem Loop ausgeführt werden.
*/
struct blinker
{
    bool enable = false;
    uint8_t pin1 = 0;
    bool neg1 = false;
    uint8_t pin2 = 0;
    bool neg2 = false;
    uint16_t blinkTime = 0;
    unsigned long lastblink = 0;
    bool blinkState = false;

    // PinNr.1, Negierung1, PinNr.2, Negierung2, Blinkzeit [ms], Startzustand
    void init(uint8_t, bool, uint8_t, bool, uint16_t, bool);

    void poll();

    void on();
    void off();
};

#endif