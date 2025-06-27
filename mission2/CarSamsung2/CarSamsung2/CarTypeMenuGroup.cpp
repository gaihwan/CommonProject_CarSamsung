#include "CarTypeMenuGroup.h"
//#include <iostream>
#include "ICommand.h"

void
CarTypeMenuGroup::printMenu(void) {
    std::cout << CLEAR_SCREEN;
    std::cout << "        ______________\n";
    std::cout << "       /|            | \n";
    std::cout << "  ____/_|_____________|____\n";
    std::cout << " |                      O  |\n";
    std::cout << " '-(@)----------------(@)--'\n";
    std::cout << "===============================\n";
    std::cout << "어떤 차량 타입을 선택할까요?\n";
    std::cout << "1. Sedan\n";
    std::cout << "2. SUV\n";
    std::cout << "3. Truck\n";
}