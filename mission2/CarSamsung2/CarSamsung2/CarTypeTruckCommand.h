#pragma once

#include <iostream>
#include "ICommand.h"

class CarTypeTruckCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Truck.\n";
    }
};