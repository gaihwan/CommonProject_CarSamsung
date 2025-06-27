#pragma once
#include <iostream>
#include "ICommand.h"

class BrakeTypeBoschCommand : public ICommand {
public:
    void Display() override {
        std::cout << "BOSCH.\n";
    }
};

class BrakeTypeContinentalCommand : public ICommand {
public:
    void Display() override {
        std::cout << "CONTINENTAL.\n";
    }
};

class BrakeTypeMandoCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Mando.\n";
    }
};

class CarTypeSedanCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Sedan.\n";
    }
};

class CarTypeSUVCommand : public ICommand {
public:
    void Display() override {
        std::cout << "SUV.\n";
    }
};

class CarTypeTruckCommand : public ICommand {
public:
    void Display() override {
        std::cout << "Truck.\n";
    }
};

class EngineTypeBrokenCommand : public ICommand {
public:
    void Display() override {
        std::cout << "고장난 엔진.\n";
    }
};

class EngineTypeGMCommand : public ICommand {
public:
    void Display() override {
        std::cout << "GM.\n";
    }
};

class EngineTypeToyotaCommand : public ICommand {
public:
    void Display() override {
        std::cout << "TOYOTA.\n";
    }
};

class EngineTypeWiaCommand : public ICommand {
public:
    void Display() override {
        std::cout << "WIA.\n";
    }
};


class SteeringTypeBoschCommand : public ICommand {
public:
    void Display() override {
        std::cout << "BOSCH.\n";
    }
};

class SteeringTypeMobisCommand : public ICommand {
public:
    void Display() override {
        std::cout << "MOBIS.\n";
    }
};