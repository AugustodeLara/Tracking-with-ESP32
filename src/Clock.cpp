// Clock.cpp
#include "Clock.h"
#include <Arduino.h>

Clock::Clock(int h, int s, int m, int pm) : hr(h), sec(s), min(m), is_pm(pm) {}

int Clock::getHour() const {
    return hr;
}

int Clock::getMinute() const {
    return min;
}

int Clock::getSecond() const {
    return sec;
}

unsigned long Clock::getMillis() const {
    // Converte horas, minutos e segundos para milissegundos
    return ((hr * 60UL * 60UL) + (min * 60UL) + sec) * 1000UL;
}

void Clock::setClock(int h, int s, int m, int pm) {
    hr = h;
    sec = s;
    min = m;
    is_pm = pm;
}

void Clock::readClock(int& h, int& s, int& m, int& pm) {
    h = hr;
    s = sec;
    m = min;
    pm = is_pm;
}

void Clock::advance() {
    sec++;
    if (sec == 60) {
        sec = 0;
        min++;
        if (min == 60) {
            min = 0;
            hr++;
            if (hr == 12) {
                hr = 0;
                is_pm = !is_pm;
            }
        }
    }
    Serial.println("Clock avançado");
}