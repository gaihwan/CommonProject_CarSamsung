#pragma once

#include "IMenuGroup.h"

enum STEERING_TYPE
{
    BOSCH_S = 1,
    MOBIS,
    STEERING_TYPE_END,
};

class RunTestMenuGroup : public IMenuGroup {
public:
    void printMenu(void) override;
private:
    QUESTION_TYPE Step;
};