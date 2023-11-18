// ClockCalendar.h
#ifndef CLOCK_CALENDAR_H
#define CLOCK_CALENDAR_H

#include "Clock.h"
#include "Calendar.h"
#include "Arduino.h"

class ClockCalendar : public Clock, public Calendar {
public:
    ClockCalendar();  // Adicionado o construtor padrão
    ClockCalendar(int mt, int d, int y, int h, int m, int s, int pm);
    void advance();
    int calculateTimeDifference(const ClockCalendar& other) const;
    int getSecondsSinceMidnight() const;
    unsigned long getMillis() const; 
    String currentTime() const ;
};

#endif // CLOCK_CALENDAR_H
