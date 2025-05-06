#include "ClockTime.h"

ClockTime::ClockTime() { }

ClockTime::ClockTime(std::string timeStr) {
    parse(timeStr);
}

ClockTime::ClockTime(int hour, int minute)
    : hour(hour), minute(minute) { }

ClockTime::~ClockTime() { }

bool ClockTime::parse(std::string timeStr) {
    if (timeStr.length() != 5 || timeStr[2] != ':') return false;

    if (!std::isdigit(timeStr[0]) || !std::isdigit(timeStr[1]) ||
        !std::isdigit(timeStr[3]) || !std::isdigit(timeStr[4])) return false;

    hour = std::stoi(timeStr.substr(0, 2));
    minute = std::stoi(timeStr.substr(3, 2));

    if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) return false;
    
    return true;
}

std::string ClockTime::str() const {
    std::ostringstream oss;
    oss << (hour < 10 ? "0" : "") << hour << ":" << (minute < 10 ? "0" : "") << minute;
    return oss.str();
}

int ClockTime::roundHrUp() {
    if (minute == 0) return hour;
    else return hour + 1;
}

std::istream& operator>> (std::istream& is, ClockTime& time) {
    std::string timeStr;
    if (std::getline(is, timeStr, ' ')) {
        if (!time.parse(timeStr)) {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const ClockTime& time) {
    os << time.str();
    return os;
}

bool ClockTime::operator<(const ClockTime& other) const {
    if (hour < other.hour) {
        return true;
    }
    if (hour == other.hour && minute < other.minute) {
        return true;
    }
    return false;
}

bool ClockTime::operator>(const ClockTime& other) const {
    if (hour > other.hour) {
        return true;
    }
    if (hour == other.hour && minute > other.minute) {
        return true;
    }
    return false;
}

ClockTime ClockTime::operator+(const ClockTime& other) const {
    int totalMnThis = hour * 60 + minute;
    int totalMnOther = other.hour * 60 + other.minute;

    int diffMn = totalMnThis + totalMnOther;
    int diffHr = diffMn / 60;
    diffMn %= 60;

    return ClockTime(diffHr, diffMn);
}

ClockTime ClockTime::operator-(const ClockTime& other) const {
    int totalMnThis = hour * 60 + minute;
    int totalMnOther = other.hour * 60 + other.minute;

    int diffMn = std::abs(totalMnThis - totalMnOther);
    int diffHr = diffMn / 60;
    diffMn = diffMn % 60;

    return ClockTime(diffHr, diffMn);
}