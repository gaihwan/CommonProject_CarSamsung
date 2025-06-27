#pragma once

// === Command 인터페이스 ===
class ICommand {
public:
    //virtual void Execute() = 0;
    virtual void Display(void) = 0;
    virtual ~ICommand() = default;
};