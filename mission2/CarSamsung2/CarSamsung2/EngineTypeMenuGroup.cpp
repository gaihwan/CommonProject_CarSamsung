#include "EngineTypeMenuGroup.h"
//#include <iostream>
#include "ICommand.h"

void
EngineTypeMenuGroup::printMenu(void) {
    std::cout << CLEAR_SCREEN;
    std::cout << "어떤 엔진을 탑재할까요?\n";
    std::cout << "0. 뒤로가기\n";
    std::cout << "1. GM\n";
    std::cout << "2. TOYOTA\n";
    std::cout << "3. WIA\n";
    std::cout << "4. 고장난 엔진\n";
}
