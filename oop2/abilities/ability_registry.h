#ifndef OOP_PROG_ABILITY_REGISTRY_H
#define OOP_PROG_ABILITY_REGISTRY_H

#include "abilitiy.h"
#include <memory>
#include <vector>
#include <functional>

class Player;

typedef std::shared_ptr<Ability>(*AbilityCreator)(Player & user, Player &target);

class AbilityRegistry {
    std::vector<AbilityCreator> creators;
public:
    static AbilityRegistry &instance();

    typedef std::vector<AbilityCreator>::const_iterator iterator;
    iterator begin() const { return creators.begin(); }
    iterator end() const { return creators.end(); }

    AbilityCreator getRandomCreator();
    bool registerAbility(AbilityCreator creator);
};


#endif //OOP_PROG_ABILITY_REGISTRY_H
