#pragma once

#include <iostream>
#include "ICommand.h"

class CarTypeSedanCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Sedan.\n";
    }
};