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

std::shared_ptr<Ability> CreateRocket(Player &user, Player &target)
{
    return std::make_shared<Rocket>(target.SManager);
}

static bool registration = AbilityRegistry::instance().registerAbility(CreateRocket);