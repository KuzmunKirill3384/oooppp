#ifndef ROCKET_BARRAGE_HPP_
#define ROCKET_BARRAGE_HPP_

#include "abilitiy.h"
#include "../manager.h"

class Rocket : public Ability {
    ShipManager &ships;
public:
    explicit Rocket(ShipManager &ships) : ships(ships) {}
    std::string use() const;
};

#endif