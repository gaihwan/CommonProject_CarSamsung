#pragma once

#include <iostream>
#include "ICommand.h"

class SteeringTypeMobisCommand : public ICommand {
public:
    void Display() override {
        std::cout << "MOBIS.\n";
    }
};