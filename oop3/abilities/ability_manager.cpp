#include "ability_manager.h"
#include "ability_registry.h"
#include <vector>
#include <algorithm>

AbilityManager::AbilityManager() {
    std::vector<AbilityCreator*> creators;

    for (const auto &creator: AbilityRegistry::instance()) {
        creators.push_back(creator);
    }

    std::random_shuffle(creators.begin(), creators.end());

    for (const auto &creator: creators) {
        abilities.push_back(creator);
    }
}

std::string AbilityManager::useAbility(Player &user, Player &target)
{
    if (abilities.size() == 0) {
        throw AbilityFailureException();
    }

    auto ability = abilities.front()->create(user, target);
    abilities.pop_front();

    return ability->use();
}

void AbilityManager::giveNewAbility()
{
    abilities.push_back(AbilityRegistry::instance().getRandomCreator());
}

void to_json(json &j, const AbilityManager &manager)
{
    j = json::array();
    for (const AbilityCreator *ability : manager.abilities) {
        j.push_back(ability->getName());
    }
}

AbilityManager::AbilityManager(const json &j)
{
    for (std::string name : j) {
        abilities.push_back(AbilityRegistry::instance().getCreatorByName(name.c_str()));
    }
}
