#include "ability_registry.h"

AbilityRegistry &AbilityRegistry::instance()
{
    static AbilityRegistry registry;
    return registry;
}


AbilityCreator AbilityRegistry::getRandomCreator()
{
    return creators[rand() % creators.size()];
}

bool AbilityRegistry::registerAbility(AbilityCreator creator)
{
    creators.push_back(creator);
    return true;
}
