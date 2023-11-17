// Calendar.cpp
#include "Calendar.h"
#include <Arduino.h>

Calendar::Calendar(int m, int d, int y) : mo(m), day(d), yr(y) {}

void Calendar::setCalendar(int m, int d, int y) {
    mo = m;
    day = d;
    yr = y;
}

void Calendar::readCalendar(int& m, int& d, int& y) {
    m = mo;
    d = day;
    y = yr;
}

void Calendar::advance() {
    day++;
    int daysInMonth;

    // Define o número de dias no mês atual
    switch (mo) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            daysInMonth = (yr % 4 == 0 && (yr % 100 != 0 || yr % 400 == 0)) ? 29 : 28; // Verifica ano bissexto
            break;
        default:
            daysInMonth = 0; // Mês inválido
    }

    if (day > daysInMonth) {
        day = 1;
        mo++;
        if (mo > 12) {
            mo = 1;
            yr++;
        }
    }
    Serial.println("Calendário avançado");

}
