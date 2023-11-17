// Clock.h
#ifndef CLOCK_H
#define CLOCK_H

class Clock {
protected:
    int hr, min, sec, is_pm;

public:
    Clock(int h, int s, int m, int pm);
    void setClock(int h, int s, int m, int pm);
    void readClock(int& h, int& s, int& m, int& pm);
    void advance();
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
};

#endif // CLOCK_H
