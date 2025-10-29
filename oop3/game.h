#ifndef OOP_PROG_GAME_H
#define OOP_PROG_GAME_H

#include "game_state.h"

enum class GameResult {
    TryAgain,
    Quit
};

class Game {
    GameState state;

    vector<int> numOfShips;
    int fieldWidth;
    int fieldHeight;

public:
    Game();

    void createShips();
    void createField();
    GameResult playRound();
    void load();
    void save();
    void doCommand(std::string &command);
    void doOpponentMove();
    GameResult fight();
};

#endif
