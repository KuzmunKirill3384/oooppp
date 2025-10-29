#ifndef OOP_PROG_ABILITY_REGISTRY_H
#define OOP_PROG_ABILITY_REGISTRY_H

#include "abilitiy.h"
#include <memory>
#include <set>

class Player;

struct AbilityCreator {
    virtual std::shared_ptr<Ability> create(Player &user, Player &target) const = 0;
    virtual const char* getName() const = 0;
};

class AbilityRegistry {
    std::set<AbilityCreator*> creators;
public:
    static AbilityRegistry &instance();

    typedef std::set<AbilityCreator*>::const_iterator iterator;
    iterator begin() const { return creators.begin(); }
    iterator end() const { return creators.end(); }

    const AbilityCreator *getRandomCreator();
    const AbilityCreator *getCreatorByName(const char *name);
    bool registerAbility(AbilityCreator *creator);
};


#endif //OOP_PROG_ABILITY_REGISTRY_H
