#ifndef OOP_PROG_GAME_STATE_H
#define OOP_PROG_GAME_STATE_H

#include <memory>
#include <nlohmann/json.hpp>
#include "abilities/player.h"
#include "abilities/exception.h"

class GameStateUndefinedException : public GameException {
    const char *what() { return "Game state is not set up yet"; }
};

class GameState {
public:
    std::unique_ptr<Player> player;
    std::unique_ptr<Player> opponent;

    friend std::istream &operator>>(std::istream &is, GameState &state);
    friend std::ostream &operator<<(std::ostream &os, const GameState &state);
};

#endif
