#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

#include "ICommand.h"

// === Menu Component (Composite 패턴) ===
class MenuComponent {
public:
    virtual void Display(int indent = 0) = 0;
    //virtual void Click() = 0;
    virtual ~MenuComponent() = default;
};

// === Leaf 메뉴 항목 ===
class MenuItem : public MenuComponent {
    std::string name;
    std::unique_ptr<ICommand> command;

public:
    MenuItem(const std::string& n, std::unique_ptr<ICommand> c)
        : name(n), command(std::move(c)) {}

    //void Display(int indent = 0) override {
    //    //std::cout << std::string(indent, ' ') << "- " << name << '\n';
    //}
    void Display(int index = 1) override {
        std::cout << index << ". " << name << '\n';
    }

    //void Click() override {
    //    if (command) command->Execute();
    //}
};

// === Composite 메뉴 그룹 ===
class MenuGroup : public MenuComponent {
    std::string name;
    std::vector<std::unique_ptr<MenuComponent>> children;

public:
    MenuGroup(const std::string& n) : name(n) {}

    void Add(std::unique_ptr<MenuComponent> child) {
        children.push_back(std::move(child));
    }

    void Display(int indent = 0) override {
        //std::cout << std::string(indent, ' ') << "[ " << name << " ]\n";
        int index = 1;
        for (auto& child : children) {
            //child->Display(indent + 2);
            child->Display(index++);

        }
    }

    //void Click() override {
    //    std::cout << "Group \"" << name << "\" clicked. (No action)\n";
    //}

    // Optional: access child
    MenuComponent* GetChild(size_t index) {
        if (index < children.size())
            return children[index].get();
        return nullptr;
    }
};