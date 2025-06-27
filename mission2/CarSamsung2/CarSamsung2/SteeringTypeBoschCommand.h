#pragma once

#include <iostream>
#include "ICommand.h"

class SteeringTypeBoschCommand : public ICommand {
public:
    void Display() override {
        std::cout << "BOSCH".\n";
    }
};