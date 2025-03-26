/*
    ======== ÜBUNG ============

    - Erstelle eine Struktur analogblinker
    - Die Struktur soll einen PWM-Blinker realisieren

 */

#include <Arduino.h>
#include "helper.h"
#include "analogblinker.h"

#define LED1 5    // Low-side switch (leuchtet mit LOW)
#define LED2 6    // High-side switch (leuchtet mit HIGH)
#define TASTER1 3 // HIGH wenn gedrückt
#define TASTER2 2 // LOW wenn gedrückt
#define POTI A7   // Poti an A7

#define DB_ZEIT 50
#define BLINKTIME 300
#define LONGPRESSTIME 1000

#define ANALOGBLINKER_POLLTIME 10 // ms
#define ANALOGBLINKER_MIN 100     // ms
#define ANALOGBLINKER_MAX 3000    // ms

// Instanzieren der Strukturen
button taster1;

analogblinker a_blinker;

void setup()
{
    Serial.begin(115200);
    Serial.println("..Start..\n");

    // Initialisierung der Strukturen
    taster1.init(TASTER1, false, DB_ZEIT, LONGPRESSTIME);
    a_blinker.init(LED1, LED2, BLINKTIME, ANALOGBLINKER_POLLTIME, true, true);
}

void loop()
{
    taster1.poll();
    a_blinker.poll();

    a_blinker.blinkTime = ((((ANALOGBLINKER_MAX - ANALOGBLINKER_MIN) / 1023.0) * analogRead(POTI)) + 100) / 4;

    if (taster1.longpress)
    {
        a_blinker.sync = !a_blinker.sync;
        if (a_blinker.sync)
        {
            Serial.println("Sync eingeschaltet");
        }
        else
        {
            Serial.println("Sync ausgeschaltet");
        }
    }
    else if (taster1.falling)
    {
        a_blinker.enable = !a_blinker.enable;
        if (a_blinker.enable)
        {
            Serial.println("Blinker eingeschaltet");
        }
        else
        {
            Serial.println("Blinker ausgeschaltet");
        }
    }
}
