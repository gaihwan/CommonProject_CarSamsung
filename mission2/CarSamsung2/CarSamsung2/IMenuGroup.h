#pragma once
#include <iostream>
#include <vector>

#define CLEAR_SCREEN "\033[H\033[2J"

class IMenuGroup {
public:
    virtual void printMenu(void) = 0;
};

// === Composite 메뉴 그룹 ===
class MenuGroup_test : public IMenuGroup {
    std::string name;
    std::vector<std::unique_ptr<IMenuGroup>> children;

public:
    MenuGroup_test(const std::string& n) : name(n) {}

    void Add(std::unique_ptr<IMenuGroup> child) {
        children.push_back(std::move(child));
    }

    void Display(int indent = 0) {
        for (auto& child : children) {
            child->printMenu();
        }
    }

    //void Click() override {
    //    std::cout << "Group \"" << name << "\" clicked. (No action)\n";
    //}

    // Optional: access child
    IMenuGroup* GetChild(size_t index) {
        if (index < children.size())
            return children[index].get();
        return nullptr;
    }
};


enum QUESTION_TYPE
{
    CAR_TYPE = 1,
    ENGINE_TYPE,
    BRAKE_SYSTEM_TYPE,
    STEERING_SYSTEM_TYPE,
    RUN_TEST,
    QUESTION_TYPE_END,
};