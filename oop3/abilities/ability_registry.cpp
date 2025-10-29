#include "ability_registry.h"
#include <cstring>

AbilityRegistry &AbilityRegistry::instance()
{
    static AbilityRegistry registry;
    return registry;
}


const AbilityCreator *AbilityRegistry::getRandomCreator()
{
    std::set<AbilityCreator*>::iterator random_it = creators.begin();
    std::advance(random_it, rand() % creators.size());
    return *random_it;
}

const AbilityCreator *AbilityRegistry::getCreatorByName(const char *name)
{
    for (AbilityCreator *creator : creators) {
        if (!strcmp(creator->getName(), name)) {
            return creator;
        }
    }

    return nullptr;
}

bool AbilityRegistry::registerAbility(AbilityCreator *creator)
{
    creators.insert(creator);
    return true;
}
