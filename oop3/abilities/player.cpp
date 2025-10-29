#include "player.h"
#include "ability_manager.h"
#include <iostream>

void Player::attack(GameBoard &field)
{
    AttackResult res1 = field.attackCell(cursor.x, cursor.y);
    AttackResult res2 = AttackResult::Nothing;

    if (double_damage_flag) {
        res2 = field.attackCell(cursor.x, cursor.y);
        double_damage_flag = false;
    }

    if (res1 == AttackResult::ShipDestroyed || res2 == AttackResult::ShipDestroyed) {
        std::cout << "You got new ability" << std::endl;
        abilities.giveNewAbility();
    }
}

Player::Player(const json &j) :
    Field(j["field"]), SManager(j["smanager"]), cursor(j["cursor"]),
    abilities(j["abilities"]), double_damage_flag(j["double_damage_flag"])
{
    for (Ship &ship : SManager) {
        Field.placeShip(ship, ship.getX(), ship.getY(), ship.isHorizontalOrientation());
    }
}

void to_json(json &j, const Player &player)
{
    j = json{
        {"field", player.Field},
        {"smanager", player.SManager},
        {"cursor", player.cursor},
        {"abilities", player.abilities},
        {"double_damage_flag", player.double_damage_flag}
    };
}
