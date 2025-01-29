#include "game_state.h"

using namespace nlohmann;

std::istream &operator>>(std::istream &is, GameState &state)
{
    json j;
    is >> j;

    state.player = make_unique<Player>(j["player"]);
    state.opponent = make_unique<Player>(j["opponent"]);

    return is;
}

std::ostream &operator<<(std::ostream &os, const GameState &state)
{
    json j;

    if (!state.player || !state.opponent) {
        throw GameStateUndefinedException();
    }

    j["player"] = *state.player;
    j["opponent"] = *state.opponent;
    
    os << j.dump();
    return os;
}
