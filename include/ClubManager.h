#ifndef _CLUB_MANAGER_H
#define _CLUB_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "ClockTime.h"

class ClubManager {
    public:
        ClubManager(std::string filename);
        ~ClubManager();

        bool process();

    private:
        std::string filename;
        std::string output;

        int deskCount;
        ClockTime openTime, closeTime;
        int hourPrice;

        bool read_error(std::string& line);
        bool read_line(std::istream& in, std::string& line, std::istringstream& iss);
        bool check_leftover(std::istringstream& iss, std::string& line);
};

#endif