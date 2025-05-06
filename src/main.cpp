#include "ClubManager.h"

int main() {
    ClubManager* manager = new ClubManager("input.txt");
    if (!manager->process()) {
        std::cout << "Error has occured; program stopped" << std::endl;
        return 1;
    }

    return 0;
}