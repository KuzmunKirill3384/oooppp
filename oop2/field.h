#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "ship.h"
#include <memory>

struct CellStatus {
    Ship *ship;
    int segment_index;
    bool has_fog;
};

class GameBoard {
public:
    // Constructor
    GameBoard(int width, int height);

    // Copy constructor
    GameBoard(const GameBoard& other);

    // Copy assignment operator
    GameBoard& operator=(const GameBoard& other);

    // Move constructor
    GameBoard(GameBoard&& other);

    // Move assignment operator
    GameBoard& operator=(GameBoard&& other);

    // Place a ship
    void placeShip(Ship& ship, int x, int y, bool isHorizontal);

    // Attack a cell
    AttackResult attackCell(int x, int y);

    // Draw the game field
    void printField();

    // Get the status of a cell
    CellStatus &getCellStatus(int x, int y);

    // Create a random ship
    Ship* createRandomShip(int length);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width;
    int height;
    std::vector<std::vector<CellStatus>> board;
    // Check if the cell is occupied or adjacent to occupied cells
    bool isOccupiedOrAdjacent(int x, int y) const;
};

#endif // FIELD_H