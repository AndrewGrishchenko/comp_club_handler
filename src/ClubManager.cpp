#include "ClubManager.h"

ClubManager::ClubManager(std::string filename)
    : filename(filename) { }

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
    desks.resize(deskCount);

    read_line(in, line, iss);
    if (!(iss >> openTime >> closeTime) || !check_leftover(iss)) return read_error(line);
    output << openTime << std::endl;

    read_line(in, line, iss);
    if (!(iss >> hourPrice) || !check_leftover(iss)) return read_error(line);

    ClockTime current_time;
    int id;
    std::string client;
    int deskId;
    while(read_line(in, line, iss)) {
        if (!(iss >> current_time >> id >> client)) return read_error(line);
        if (id != 2 && !check_leftover(iss)) return read_error(line);

        output << line << "\n";

        if (id == 1) {
            if (current_time < openTime || current_time > closeTime) add_outcome_entry(current_time, 13, "NotOpenYet"); 
            else if (visitors.find(client) != visitors.end()) add_outcome_entry(current_time, 13, "YouShallNotPass");
            else visitors.insert(client);
        } else if (id == 2) {
            if (!(iss >> deskId) || !check_leftover(iss)) return read_error(line);

            if (visitors.find(client) == visitors.end()) add_outcome_entry(current_time, 13, "ClientUnknown");
            else if (!desks[deskId-1].client.empty()) add_outcome_entry(current_time, 13, "PlaseIsBusy");
            else {
                desks[deskId-1].startTime = current_time;
                desks[deskId-1].client = client;
            }
        } else if (id == 3) {
            bool hasFree = std::any_of(desks.begin(), desks.end(), [](const deskData& desk) {
                return desk.client.empty();
            });
            if (hasFree) add_outcome_entry(current_time, 13, "ICanWaitNoLonger!");
            else if (visitorsQueue.size() > deskCount) {
                visitors.erase(client);
                add_outcome_entry(current_time, 11, client);
            } else {
                visitorsQueue.push(client);
            }

        } else if (id == 4) {
            if (visitors.find(client) == visitors.end()) add_outcome_entry(current_time, 13, "ClientUnknown");
            else {
                visitors.erase(client);
                auto desk = std::find_if(desks.begin(), desks.end(), [&](const deskData& desk) {
                    return desk.client == client;
                });
                desk->client = "";
                desk->earnings += hourPrice * (current_time - desk->startTime).roundHrUp();
                desk->totalTime = desk->totalTime + (current_time - desk->startTime);
                
                if (visitorsQueue.size() != 0) {
                    desk->startTime = current_time;
                    desk->client = visitorsQueue.front();
                    add_outcome_entry(current_time, 12, visitorsQueue.front(), (desk - desks.begin() + 1));
                    visitorsQueue.pop();
                }
            }
        } else {
            std::cout << "Unknown id\n";
            return false;
        }
    }

    for (auto& desk : desks) {
        if (desk.client != "") {
            desk.earnings += hourPrice * (closeTime - desk.startTime).roundHrUp();
            desk.totalTime = desk.totalTime + (closeTime - desk.startTime);
            add_outcome_entry(closeTime, 11, client);
            visitors.erase(client);
        }
    }

    for (const auto& client : visitors) {
        add_outcome_entry(closeTime, 11, client);
    }
    visitors.clear();
    
    output << closeTime << std::endl;

    for (int i = 0; i < deskCount; i++) {
        output << (i + 1) << " " << desks[i].earnings << " " << desks[i].totalTime << std::endl;
    }

    std::cout << output.str();

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

template <typename... Args>
void ClubManager::add_outcome_entry(ClockTime entryTime, int id, const Args&... args) {
    output << entryTime << " " << id;
    ((output << " " << args), ...);
    output << std::endl;
}