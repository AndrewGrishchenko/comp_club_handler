#include "ClubManager.h"

ClubManager::ClubManager(std::string filename)
    : filename(filename) { }

ClubManager::~ClubManager() {

}

bool ClubManager::process() {
    std::ifstream in(filename);

    if (!in.is_open()) {
        std::cout << "File \"" << filename  << "\" not found!" << std::endl;
        return false;
    }

    std::string line;
    std::istringstream iss;

    read_line(in, line, iss);
    if (!(iss >> deskCount) || !check_leftover(iss)) return read_error(line);

    read_line(in, line, iss);
    if (!(iss >> openTime >> closeTime) || !check_leftover(iss)) return read_error(line);

    read_line(in, line, iss);
    if (!(iss >> hourPrice) || !check_leftover(iss)) return read_error(line);

    ClockTime current_time;
    int id;
    std::string client;
    int deskId;
    while(read_line(in, line, iss)) {
        if (!(iss >> current_time >> id >> client)) return read_error(line);

        //TODO: add output entry

        switch (id) {
            case 1:
                //client arrived
                //<time> 1 <client>
                
                //TODO: if not working houts, "NotOpenYet"
                //TODO: if already in club, "YouShallNotPass"
                break;
            case 2:
                //client sits to desk
                //<time> 2 <client> <desk>
                
                //TODO: if desk is busy, "PlaceIsBusy"
                //TODO: if client trying to sit to desk he is sitting at, "PlaceIsBusy"
                //TODO: if client not in club, "ClientUnknown"
                break;
            case 3:
                //client is waiting
                //<time> 3 <client>

                //TODO: if there are free desks, "ICanWaitNoLonger!"
                //TODO: if queue bigger than deskCount, gen event 11 (client leaves)
                break;
            case 4:
                //client leaves
                //<time> 4 <client>

                //TODO: if client is not in club, "ClientUnknown"
                //TODO: his desk is freeing now, gen event 12 (client seats to desk)
                break;
        }

        //outcome
        //11 -- client leaves
        //<time> 11 <client>
        //gen for every client when closing in alphabetical order
        
        //12 -- client sits to desk
        //<time> 12 <client> <desk>
        //gen for first client in queue when desk is freeing
        
        //13 -- error
        //<time> 13 <error>
    }

    return true;
}

bool ClubManager::read_error(std::string& line) {
    std::cout << line << std::endl;
    return false;
}

bool ClubManager::read_line(std::istream& in, std::string& line, std::istringstream& iss) {
    if (!std::getline(in, line)) {
        std::cout << line << std::endl;
        return false;
    }

    if (line.empty()) return false;

    iss.clear();
    iss.str(line);
    return true;
}

bool ClubManager::check_leftover(std::istringstream& iss) {
    if (iss.peek() != EOF) {
        return false;
    }
    return true;
}