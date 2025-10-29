#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../field.h"
#include "../manager.h"
#include "../cursor.h"
#include "ability_manager.h"

class Player {
public:
    GameBoard Field;
    ShipManager SManager;
    Cursor cursor;
    AbilityManager abilities;
    bool double_damage_flag = false;

    Player(GameBoard &field, ShipManager &shipManager)
        : Field(field), SManager(shipManager), cursor(0, 0), double_damage_flag(false)
    {}

    void attack();
};

#endif