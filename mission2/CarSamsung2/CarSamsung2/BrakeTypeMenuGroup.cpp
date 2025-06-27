#include "BrakeTypeMenuGroup.h"
//#include <iostream>
#include "ICommand.h"


void
BrakeTypeMenuGroup::printMenu(void) {
    std::cout << "어떤 제동장치를 선택할까요?\n";
    std::cout << "0. 뒤로가기\n";
    std::cout << "1. MANDO\n";
    std::cout << "2. CONTINENTAL\n";
    std::cout << "3. BOSCH\n";
}