#include "game.h"
#include "abilities/exception.h"
#include "field.h"
#include "manager.h"
#include "ship.h"
#include <iostream>
#include <memory>
#include <fstream>

Game::Game()
    : numOfShips(4, 1), fieldWidth(10), fieldHeight(10)
{}

void Game::createShips()
{
    cout << "Please enter numbers of ships: 'Number of one-deck ship' 'two-deck' 'three-deck' 'four-deck' without '.'\n";
    cin >> numOfShips[0] >> numOfShips[1] >> numOfShips[2] >> numOfShips[3];

    int field_size = state.player->Field.getWidth() * state.player->Field.getHeight();

    while (numOfShips[0]*9 + numOfShips[1]*12 + numOfShips[2]*15 + numOfShips[3]*18 > field_size ||
           numOfShips[0] < 0 || numOfShips[1] < 0 || numOfShips[2] < 0 || numOfShips[3] < 0) {
        cout << "Number of ships is too big for this field, or some value is less than 0.\n";
        cin >> numOfShips[0] >> numOfShips[1] >> numOfShips[2] >> numOfShips[3];
    }

    state.player->SManager = ShipManager(numOfShips);
    state.opponent->SManager = ShipManager(numOfShips);

    for (Ship &ship : state.player->SManager) {
        state.player->Field.placeShipRandomly(ship);
    }

    for (Ship &ship : state.opponent->SManager) {
        state.opponent->Field.placeShipRandomly(ship);
    }
}

void Game::createField()
{
    cout << "Please enter size of field: ";
    cin >> fieldWidth >> fieldHeight;

    state.player = std::make_unique<Player>(GameBoard(fieldWidth, fieldHeight), ShipManager());
    state.opponent = std::make_unique<Player>(GameBoard(fieldWidth, fieldHeight), ShipManager());
}

GameResult Game::fight()
{
    while (true) {
        GameResult res = this->playRound();
        if (res == GameResult::Quit) {
            break;
        }

        if (state.player->SManager.getNumAliveShips() > 0) {
            std::cout << "YOU WON!!!!\n";
            std::cout << "NEXT ROUND!!!!\n";
            
            state.opponent->Field = GameBoard(fieldWidth, fieldHeight);
            state.opponent->SManager = ShipManager(numOfShips);

            for (Ship &ship : state.opponent->SManager) {
                state.opponent->Field.placeShipRandomly(ship);
            }
        }
        else {
            std::cout << "YOU LOSE!!!!\n";
            return GameResult::TryAgain;
        }
    }

    return GameResult::Quit;
}

void Game::doCommand(std::string &command)
{
    if (command == "cursor") {
        cout << "Enter the coordinates: 'x' 'y': \n";
        cin >> state.player->cursor.x >> state.player->cursor.y;
    }
    else if (command == "attack") {
        state.player->attack(state.opponent->Field);
        doOpponentMove();
    }
    else if (command == "ability") {
        std::cout << state.player->abilities.useAbility(*state.player, *state.opponent) << std::endl;
    }
    else if (command == "save") {
        this->save();
    }
    else if (command == "load") {
        this->load();
    }
    else {
        cout << "Unknown command!\n";
    }
}

void Game::save()
{
    std::ofstream ofs("save.json");
    ofs << state;
    ofs.close();
}

void Game::load()
{
    try {
        std::ifstream ifs("save.json");
        ifs >> state;
        ifs.close();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "Failed to read save.json\n";
    }

    fieldWidth = state.player->Field.getWidth();
    fieldHeight = state.player->Field.getHeight();

    for (Ship &ship : state.player->SManager) {
        numOfShips[ship.getLength() - 1]++;
    }
}

void Game::doOpponentMove()
{
    while (true) {
        int x = rand() % fieldWidth;
        int y = rand() % fieldHeight;

        CellStatus &cell = state.player->Field.getCellStatus(x, y);
        if (cell.has_fog || (cell.ship != nullptr && cell.ship->getSegmentState(cell.segment_index) != SegmentState::Destroyed)) {
            state.opponent->cursor = {x, y};
            state.opponent->attack(state.player->Field);
            break;
        }
    }
}

GameResult Game::playRound()
{
    while (state.player->SManager.getNumAliveShips() > 0 && state.opponent->SManager.getNumAliveShips() > 0) {
        std::cout << "YOUR FIELD:\n";
        state.player->Field.printField();

        std::cout << "\nOPPONENT'S FIELD:\n";
        state.opponent->Field.printField();

        cout << "Enter command (cursor/attack/ability/quit): ";
        std::string command;
        cin >> command;

        if (command == "quit") {
            return GameResult::Quit;
        }

        try {
            doCommand(command);
        }
        catch (GameException &e) {
            cout << e.what() << std::endl;
        }
    }

    return GameResult::TryAgain;
}
