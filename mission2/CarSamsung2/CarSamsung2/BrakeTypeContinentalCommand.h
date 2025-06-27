#pragma once

#include <iostream>
#include "ICommand.h"

class BrakeTypeContinentalCommand : public ICommand {
public:
    void Display() override {
        std::cout << "CONTINENTAL.\n";
    }
};