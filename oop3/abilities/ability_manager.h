//
// Created by User on 26.12.2024.
//

#ifndef OOP_PROG_ABILITY_MANAGER_H
#define OOP_PROG_ABILITY_MANAGER_H

#include <deque>
#include <nlohmann/json.hpp>

using namespace nlohmann;

#include "ability_registry.h"
#include "exception.h"

class AbilityFailureException : public GameException {
public:
    const char *what() { return "you have no abilities"; }
};

class AbilityManager {
    std::deque<const AbilityCreator*> abilities;
public:
    AbilityManager();
    AbilityManager(const json &j);

    std::string useAbility(Player &user, Player &target);
    void giveNewAbility();

    friend void to_json(json &j, const AbilityManager &manager);
};


#endif //OOP_PROG_ABILITY_MANAGER_H
