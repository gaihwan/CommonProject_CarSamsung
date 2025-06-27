#include "SteeringTypeMenuGroup.h"

void
SteeringTypeMenuGroup::printMenu(void) {
    std::cout << CLEAR_SCREEN;
    std::cout << "어떤 조향장치를 선택할까요?\n";
    std::cout << "0. 뒤로가기\n";
    std::cout << "1. BOSCH\n";
    std::cout << "2. MOBIS\n";
}