#ifndef _CLUB_MANAGER_H
#define _CLUB_MANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <set>
#include <vector>
#include <queue>

#include <algorithm>

#include "ClockTime.h"

class ClubManager {
    public:
        ClubManager(std::string filename);

        bool process();
        std::string get_output();

    private:
        std::string filename;
        std::ostringstream output;

        struct deskData {
            ClockTime startTime;
            std::string client;
            int earnings;
            ClockTime totalTime;

            deskData() : client(""), earnings(0) { }
        };

        std::set<std::string> visitors;
        std::queue<std::string> visitorsQueue;
        std::vector<deskData> desks;

        int deskCount;
        ClockTime openTime, closeTime;
        int hourPrice;

        bool read_error(std::string& line);
        bool read_line(std::istream& in, std::string& line, std::istringstream& iss);
        bool check_leftover(std::istringstream& iss);
        
        template <typename... Args>
        void add_outcome_entry(ClockTime entryTime, int id, const Args&... args);
};

#endif