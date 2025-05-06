#include "ClubManager.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "No file specified. Exiting..." << std::endl;
        return 1;
    }

    ClubManager* manager = new ClubManager(argv[1]);
    if (!manager->process()) {
        std::cout << "Error has occured; program stopped" << std::endl;
        return 1;
    }

    return 0;
}