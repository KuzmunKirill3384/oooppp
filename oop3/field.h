#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include "ship.h"

struct CellStatus {
    Ship *ship;
    int segment_index;
    bool has_fog;

    CellStatus(Ship *ship, int segment_index, bool has_fog)
        : ship(ship), segment_index(segment_index), has_fog(has_fog)
    {}

    CellStatus(const json &j) :
        ship(nullptr), segment_index(0), has_fog(j["has_fog"])
    {}

    friend void to_json(json &j, const CellStatus &cell)
    {
        j = json{{"has_fog", cell.has_fog}};
    }
};

class GameBoard {
public:
    // Constructor
    GameBoard(int width, int height);
    GameBoard(const json &j);

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
    void placeShipRandomly(Ship &ship);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    friend void to_json(json &j, const GameBoard &board);

private:
    int width;
    int height;
    std::vector<std::vector<CellStatus>> board;
    
    bool isOccupiedOrAdjacent(int x, int y) const;
};

#endif // FIELD_H
