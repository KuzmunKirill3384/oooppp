//
// Created by User on 26.12.2024.
//

#ifndef OOP_PROG_ABILITY_MANAGER_H
#define OOP_PROG_ABILITY_MANAGER_H

#include "abilitiy.h"
#include <deque>
#include <memory>

#include "ability_registry.h"
#include "exception.h"

class AbilityFailureException : public GameException {
public:
    const char *what() { return "you have no abilities"; }
};

class AbilityManager {
    std::deque<AbilityCreator> abilities;
public:
    AbilityManager();

    std::string useAbility(Player &user, Player &target);
    void giveNewAbility();
};


#endif //OOP_PROG_ABILITY_MANAGER_H
