#pragma once
#include "IMenuGroup.h"
class RootMenuGroup : public IMenuGroup {
public:
    void printMenu(void) override;
private:
    QUESTION_TYPE Step;
};