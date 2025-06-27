#pragma once

#include <iostream>
#include "ICommand.h"

class EngineTypeToyotaCommand : public ICommand {
public:
    void Display() override {
        std::cout << "TOYOTA.\n";
    }
};