#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

#include "ICommand.h"

// === Command Factory ===
class CommandFactory {
public:
    using Creator = std::function<std::unique_ptr<ICommand>()>;

    void Register(const std::string& name, Creator creator) {
        creators[name] = creator;
    }

    std::unique_ptr<ICommand> Create(const std::string& name) {
        if (creators.find(name) != creators.end()) {
            return creators[name]();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, Creator> creators;
};
