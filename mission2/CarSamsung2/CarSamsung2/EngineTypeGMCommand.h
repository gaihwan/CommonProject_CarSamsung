#pragma once

#include <iostream>
#include "ICommand.h"

class EngineTypeGMCommand : public ICommand {
public:
    void Display() override {
        std::cout << "GM.\n";
    }
};