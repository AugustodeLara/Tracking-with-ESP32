// ClockCalendar.cpp
#include "ClockCalendar.h"

ClockCalendar::ClockCalendar() : Clock(0, 0, 0, 0), Calendar(1, 1, 2023) {}

ClockCalendar::ClockCalendar(int mt, int d, int y, int h, int m, int s, int pm)
    : Clock(h, m, s, pm), Calendar(mt, d, y) {}

void ClockCalendar::advance() {
    Clock::advance();
    Calendar::advance();
}

int ClockCalendar::calculateTimeDifference(const ClockCalendar& other) const {
    int seconds1 = getSecondsSinceMidnight();
    int seconds2 = other.getSecondsSinceMidnight();
    return seconds1 - seconds2;
}

int ClockCalendar::getSecondsSinceMidnight() const {
    int hours = getHour();
    int minutes = getMinute();
    int seconds = getSecond();

    return hours * 3600 + minutes * 60 + seconds;
}

unsigned long ClockCalendar::getMillis() const {
    return millis() + getSecondsSinceMidnight() * 1000UL;
}


String ClockCalendar::currentTime() const {
    int hours = getHour();
    int minutes = getMinute();
    int seconds = getSecond();
    String period = (is_pm) ? "PM" : "AM";

    String currentTimeStr = String(hours) + ":" + String(minutes) + ":" + String(seconds) + " " + period;

    Serial.print("XXXXXXXXXXXXXXXXX - Tempo atual: ");
    Serial.println(currentTimeStr);
    return currentTimeStr;
}


String ClockCalendar::getTimeNow() const {
    int hours = getHour();
    int minutes = getMinute();
    int seconds = getSecond();
    String period = (is_pm) ? "PM" : "AM";
    String currentTimeStr = String(hours) + ":" + String(minutes) + ":" + String(seconds) + " " + period;
    return currentTimeStr;
}
