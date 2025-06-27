#pragma once

#include "IMenuGroup.h"


enum CAR_TYPE
{
    SEDAN = 1,
    SUV,
    TRUCK,
    CAR_TYPE_END,
};

class CarTypeMenuGroup : public IMenuGroup {
public:
    void printMenu(void) override;
private:
    QUESTION_TYPE Step;
};