#include "abilities/player.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <stdexcept>
#include "abilities/ability_registry.h"

using namespace std;

int main() {
    std::cout << "Number of registered abilities: " << AbilityRegistry::instance().end() - AbilityRegistry::instance().begin() << std::endl;

    cout << "Please enter size of field (it should be > 10):";
    int fieldWidth = 10, fieldHeight = 10; //magic numbers
    cin >> fieldWidth >> fieldHeight;

    while (fieldWidth <= 10 || fieldHeight <= 10) {
        cout << "Unacceptable value.\n";
        cin >> fieldWidth >> fieldHeight;
    }

    GameBoard gameBoard(fieldWidth, fieldHeight);

    // Ввод количества кораблей
    cout << "Please enter numbers of ships: 'Number of one-deck ship' 'two-deck' 'three-deck' 'four-deck' without '.'\n";
    vector<int> numOfShips(4, 1);
    cin >> numOfShips[0] >> numOfShips[1] >> numOfShips[2] >> numOfShips[3];

    while ((numOfShips[0] + numOfShips[1] + numOfShips[2] + numOfShips[3]) * 10 > fieldWidth * fieldHeight ||
           numOfShips[0] < 0 || numOfShips[1] < 0 || numOfShips[2] < 0 || numOfShips[3] < 0) {
        cout << "Number of ships is too big for this field, or some value is less than 0.\n";
        cin >> numOfShips[0] >> numOfShips[1] >> numOfShips[2] >> numOfShips[3];
    }

    vector<Ship> shipList;

    for (int shipType = 0; shipType < 4; shipType++) {
        for (int shipCount = 0; shipCount < numOfShips[shipType]; shipCount++) {
            std::unique_ptr<Ship> ship(gameBoard.createRandomShip(shipType + 1));
            if (ship != nullptr) {
                shipList.push_back(*ship);
            }
        }
    }

    int aliveShipCount = shipList.size();
    ShipManager shipManager(aliveShipCount, shipList);

    Player player(gameBoard, shipManager);

    while (aliveShipCount != 0) {
        player.Field.printField();

        cout << "Enter command (cursor/attack/ability): ";
        std::string command;
        cin >> command;

        if (command == "cursor") {
            cout << "Enter the coordinates: 'x' 'y': \n";
            cin >> player.cursor.x >> player.cursor.y;
        }
        if (command == "attack") {
            try {
                player.attack();
            } catch (const exception& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }
        else if (command == "ability") {
            try {
                std::cout << player.abilities.useAbility(player, player) << std::endl;
            }
            catch (GameException &e) {
                cout << e.what() << std::endl;
            }
        }
        else {
            cout << "Unknown command!\n";
        }


        aliveShipCount = shipManager.getNumAliveShips();
    }

    cout << "WINNER!!!\n";
    return 0;
}