#include "RunTestMenuGroup.h"
#include <iostream>

#include "ICommand.h"

void
RunTestMenuGroup::printMenu(void)
{
    std::cout << CLEAR_SCREEN;
    std::cout << "���� ������ �ϼ��Ǿ����ϴ�.\n";
    std::cout << "� ������ �ұ��?\n";
    std::cout << "0. ó�� ȭ������ ���ư���\n";
    std::cout << "1. RUN\n";
    std::cout << "2. Test\n";
}