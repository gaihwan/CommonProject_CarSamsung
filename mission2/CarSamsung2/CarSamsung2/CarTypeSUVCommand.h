#pragma once

#include <iostream>
#include "ICommand.h"

class CarTypeSUVCommand : public ICommand {
public:
    void Display() override {
        std::cout << "SUV.\n";
    }
};