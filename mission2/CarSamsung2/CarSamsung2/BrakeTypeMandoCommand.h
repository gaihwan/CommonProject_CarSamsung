#pragma once

#include <iostream>
#include "ICommand.h"

class BrakeTypeMandoCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Mando.\n";
    }
};