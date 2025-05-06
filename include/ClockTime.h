#ifndef _CLOCK_TIME_H
#define _CLOCK_TIME_H

#include <iostream>
#include <sstream>
#include "math.h"

class ClockTime {
    public:
        ClockTime();
        ClockTime(std::string timeStr);
        ClockTime(int hour, int minute);
        ~ClockTime();

        bool parse(std::string timeStr);
        std::string str() const;
        int roundHrUp();

        friend std::istream& operator>>(std::istream& is, ClockTime& time);
        friend std::ostream& operator<<(std::ostream& os, const ClockTime& time);
        bool operator>(const ClockTime& other) const;
        bool operator<(const ClockTime& other) const;
        ClockTime operator+(const ClockTime& other) const;
        ClockTime operator-(const ClockTime& other) const;

    private:
        std::string timeStr;
        int hour;
        int minute;
};

#endif