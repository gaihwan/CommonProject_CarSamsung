#pragma once

#include <iostream>
#include "ICommand.h"

class EngineTypeBrokenCommand : public ICommand {
public:
    void Display() override {
        std::cout << "고장난 엔진.\n";
    }
};