#include "game.h"
#include <iostream>

int main() {
    srand(time(nullptr));
    
    while (true) {
        Game game;
        
        std::cout << "Do you want to load save (Y/N): ";
        std::string answer;
        std::cin >> answer;

        if (answer == "y" || answer == "Y") {
            game.load();
        }
        else {
            game.createField();
            game.createShips();
        }

        GameResult res = game.fight();
        if (res == GameResult::Quit) {
            break;
        }
    }
    
    return 0;
}
