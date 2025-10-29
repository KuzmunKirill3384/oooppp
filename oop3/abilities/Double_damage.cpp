#include "Double_damage.h"
#include "ability_registry.h"
#include "player.h"

std::string DoubleDamage::use() const
{
    double_damage_flag = true;
    return "You have double damage";
}

class DoubleDamageCreator : public AbilityCreator {
    std::shared_ptr<Ability> create(Player &user, Player &target) const
    {
        return std::make_shared<DoubleDamage>(user.double_damage_flag);
    }

    const char* getName() const { return "Double damage"; }
};

static DoubleDamageCreator creator;
static bool registration = AbilityRegistry::instance().registerAbility(&creator);
