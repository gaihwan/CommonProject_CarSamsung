#pragma once

#include <iostream>
#include "ICommand.h"

class BrakeTypeBoschCommand : public ICommand {
public:
    void Display() override {
        std::cout << "BOSCH.\n";
    }
};