#ifndef _CLOCK_TIME_H
#define _CLOCK_TIME_H

#include <iostream>
#include <sstream>

class ClockTime {
    public:
        ClockTime();
        ~ClockTime();

        bool parse(std::string timeStr);
        std::string get_str();

        friend std::istream& operator>>(std::istream& is, ClockTime& time);
        bool operator>(const ClockTime& other) const;
        bool operator<(const ClockTime& other) const;

    private:
        std::string timeStr;
        int hour;
        int minute;
};

#endif