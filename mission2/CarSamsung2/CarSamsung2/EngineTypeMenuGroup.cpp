#include "EngineTypeMenuGroup.h"
//#include <iostream>
#include "ICommand.h"

void
EngineTypeMenuGroup::printMenu(void) {
    std::cout << CLEAR_SCREEN;
    std::cout << "� ������ ž���ұ��?\n";
    std::cout << "0. �ڷΰ���\n";
    std::cout << "1. GM\n";
    std::cout << "2. TOYOTA\n";
    std::cout << "3. WIA\n";
    std::cout << "4. ���峭 ����\n";
}
