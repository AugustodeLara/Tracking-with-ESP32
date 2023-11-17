// ClockCalendar.cpp
#include "ClockCalendar.h"
#include <Arduino.h>  // Adicione esta linha

ClockCalendar::ClockCalendar(int mt, int d, int y, int h, int m, int s, int pm)
    : Clock(h, m, s, pm), Calendar(mt, d, y) {}

void ClockCalendar::advance() {
    Clock::advance();
    Calendar::advance();
}

int ClockCalendar::calculateTimeDifference(const ClockCalendar& other) const {
    // Calcula a diferença de tempo em segundos entre dois ClockCalendar
    int seconds1 = getSecondsSinceMidnight();
    int seconds2 = other.getSecondsSinceMidnight();
    return seconds1 - seconds2;
}

int ClockCalendar::getSecondsSinceMidnight() const {
    // Obtém o número total de segundos desde a meia-noite
    int hours = getHour();
    int minutes = getMinute();
    int seconds = getSecond();

    return hours * 3600 + minutes * 60 + seconds;
}

unsigned long ClockCalendar::getMillis() const {
    // Obtém o tempo atual em milissegundos desde a inicialização ou reinício
    return millis();
}
