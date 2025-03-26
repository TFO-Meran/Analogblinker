#ifndef analogblinker_h
#define analogblinker_h

#include <Arduino.h>

/*
    ----------- INFO -------------
    Diese Struktur implementiert einen analogen Blinker. Die Helligkeit
    wird über die Zeit gesteuert. Die init-Methode erwartet die Pin-Nummer
    und die Zeitgrenzen für die Helligkeit. Die poll-Methode muss bei jedem
    Loop ausgeführt werden.
*/
struct analogblinker
{
    bool sync = false, enable = false;
    uint8_t pin1 = 0, pin2 = 0, step = 0;
    uint16_t blinkTime = 0, dutycycle = 0;
    unsigned long lastpoll = 0, polltime = 0;

    // PinNr1, PinNr2, Blinkzeit[ms], Abfrage-Zeit[ms], Sync-Modus, Enable[T/F]
    void init(uint8_t, uint8_t, uint16_t, uint8_t, bool, bool);

    void poll();
};

#endif