#include "headers/switch.h"
#include "headers/const.h"

void controlRelay(int index, bool on) {
    if (index >= 0 && index < nRelays()) {
        digitalWrite(relays[index], !on ? HIGH : LOW);
        relaysState[index] = on;
    } else {
        Serial.println("Invalid relay index!");
    }
}

void setupGPIO() {
    // Inicjalizacja pinów jako wyjścia dla przekaźników
    for (int i = 0; i < nRelays(); ++i) {
        pinMode(relays[i], OUTPUT);
        digitalWrite(relays[i],true);
    }
}