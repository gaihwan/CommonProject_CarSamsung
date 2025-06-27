#pragma once
#include "IMenuGroup.h"

enum BRAKE_TYPE
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    BRAKE_TYPE_END,
};

class BrakeTypeMenuGroup : public IMenuGroup {
public:
    void printMenu(void) override;
private:
    QUESTION_TYPE Step;
};
