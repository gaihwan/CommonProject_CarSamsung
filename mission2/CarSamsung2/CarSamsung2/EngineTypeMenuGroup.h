#pragma once
#include "IMenuGroup.h"

enum ENGINE_TYPE
{
    GM = 1,
    TOYOTA,
    WIA,
    ENGIN_TYPE_END,
};


class EngineTypeMenuGroup : public IMenuGroup {
public:
    void printMenu(void) override;
private:
    QUESTION_TYPE Step;
};