#pragma once

#include <iostream>
#include "ICommand.h"

class EngineTypeWiaCommand : public ICommand {
public:
    void Display() override {
        std::cout << "WIA.\n";
    }
};