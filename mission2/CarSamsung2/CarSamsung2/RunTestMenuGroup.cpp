#include "RunTestMenuGroup.h"
#include <iostream>

#include "ICommand.h"

void
RunTestMenuGroup::printMenu(void)
{
    std::cout << CLEAR_SCREEN;
    std::cout << "멋진 차량이 완성되었습니다.\n";
    std::cout << "어떤 동작을 할까요?\n";
    std::cout << "0. 처음 화면으로 돌아가기\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}