#include "rocket.h"
#include "ability_registry.h"
#include "player.h"

std::string Rocket::use() const
{
    struct Target {
        int segment;
        Ship *ship;
    };

    std::vector<Target> targets;

    for (auto &ship : ships) {
        for (int i = 0; i < ship.getLength(); i++) {
            if (ship.getSegmentState(i) != SegmentState::Destroyed) {
                targets.push_back({ i, &ship });
            }
        }
    }

    if (targets.empty()) {
        return "All ships are already destroyed";
    }

    Target target = targets[rand() % targets.size()];
    target.ship->takeDamage(target.segment);
    return "Random ship damaged";
}

class RocketCreator : public AbilityCreator {
    std::shared_ptr<Ability> create(Player &user, Player &target) const
    {
        return std::make_shared<Rocket>(target.SManager);
    }

    const char* getName() const { return "Rocket"; }
};

static RocketCreator creator;
static bool registration = AbilityRegistry::instance().registerAbility(&creator);
