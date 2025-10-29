#include "Double_damage.h"
#include "ability_registry.h"
#include "player.h"

std::string DoubleDamage::use() const
{
    double_damage_flag = true;
    return "You have double damage";
}

std::shared_ptr<Ability> CreateDoubleDamage(Player &user, Player &target)
{
    return std::make_shared<DoubleDamage>(user.double_damage_flag);
}

static bool registration = AbilityRegistry::instance().registerAbility(CreateDoubleDamage);