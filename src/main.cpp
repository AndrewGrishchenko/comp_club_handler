#include "ClubManager.h"

int main() {
    ClubManager* manager = new ClubManager("input.txt");
    manager->process();
}