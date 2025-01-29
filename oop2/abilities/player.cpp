#include "player.h"
#include <iostream>

void Player::attack()
{
    AttackResult res1 = Field.attackCell(cursor.x, cursor.y);
    AttackResult res2 = AttackResult::Nothing;

    if (double_damage_flag) {
        res2 = Field.attackCell(cursor.x, cursor.y);
        double_damage_flag = false;
    }

    if (res1 == AttackResult::ShipDestroyed || res2 == AttackResult::ShipDestroyed) {
        std::cout << "You got new ability" << std::endl;
        abilities.giveNewAbility();
    }
}