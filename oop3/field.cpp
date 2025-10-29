#include "field.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "abilities/exception.h"
#include "ship.h"

using namespace std;

// Constructor for the game field
GameBoard::GameBoard(int width, int height)
        : width(width), height(height) {
    if (width < 0 || height < 0) {
        throw out_of_range("Negative dimensions cannot be used.");//ошибки не в конс-ре
    }
    board.resize(height, vector<CellStatus>(width, CellStatus(nullptr, 0, true)));
}

// Copy constructor (deep copy)
GameBoard::GameBoard(const GameBoard& other)
        : width(other.width), height(other.height), board(other.board) {}

// Copy assignment operator (deep copy)
GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        board = other.board;
    }
    return *this;
}

// Move constructor
GameBoard::GameBoard(GameBoard&& other)
        : width(other.width), height(other.height), board(std::move(other.board)) {
    other.width = 0;
    other.height = 0;
}

// Move assignment operator
GameBoard& GameBoard::operator=(GameBoard&& other){
    if (this != &other) {
        width = other.width;
        height = other.height;
        board = std::move(other.board);
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

// Check if the cell is occupied or adjacent to occupied cells
bool GameBoard::isOccupiedOrAdjacent(int x, int y) const {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (board[ny][nx].ship != nullptr) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Place a ship
void GameBoard::placeShip(Ship& ship, int x, int y, bool isHorizontal) {
    int shipLength = ship.getLength();

    if (isHorizontal) {
        if (x + shipLength - 1 >= width || y >= height || x < 0 || y < 0) {
            throw out_of_range("Ship placement out of board bounds.");
        }
    } else {
        if (y + shipLength - 1 >= height || x >= width || x < 0 || y < 0) {
            throw out_of_range("Ship placement out of board bounds.");
        }
    }

    for (int i = 0; i < shipLength; i++) {
        int checkX = isHorizontal ? x + i : x;
        int checkY = isHorizontal ? y : y + i;

        if (isOccupiedOrAdjacent(checkX, checkY)) {
            throw invalid_argument("Ship placement collides with another ship or is too close.");
        }
    }

    for (int i = 0; i < shipLength; i++) {
        int shipX = isHorizontal ? x + i : x;
        int shipY = isHorizontal ? y : y + i;
        board[shipY][shipX].ship = &ship;
        board[shipY][shipX].segment_index = i;
    }
}

class OutOfBoundsException : public GameException {
public:
    const char *what() { return "Attacking out of board bounds"; }
};

// Attack a cell
AttackResult GameBoard::attackCell(int x, int y) {// менять в самом корабле статус сегмн-та корабля
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBoundsException();
    }

    AttackResult res = AttackResult::Nothing;

    if (board[y][x].ship != nullptr) {
        res = board[y][x].ship->takeDamage(board[y][x].segment_index);
    }

    board[y][x].has_fog = false;
    return res;
}

// Draw the game field
void GameBoard::printField() {
    cout << "   ";

    // Print the x-coordinates with proper alignment (2 spaces for single digits)
    for (int x = 0; x < width; x++) {
        if (x < 10) {
            cout << " " << x << " "; // Single digit numbers
        } else {
            cout << x << " "; // Two-digit numbers
        }
    }
    cout << endl;

    cout << "  +";
    for (int x = 0; x < width; x++) {
        cout << "---"; // Maintain consistent width for each cell
    }
    cout << "+" << endl;

    // Print the y-coordinates with proper alignment
    for (int y = 0; y < height; y++) {
        if (y < 10) {
            cout << y << " |"; // Single digit
        } else {
            cout << y << "|";  // Two-digit
        }

        // Print the cell status
        for (int x = 0; x < width; x++) {
            if (board[y][x].has_fog) {
                cout << " # ";
            }
            else if (board[y][x].ship == nullptr) {
                cout << " . ";
            }
            else {
                switch (board[y][x].ship->getSegmentState(board[y][x].segment_index)) {
                    case SegmentState::Intact:
                        cout << " $ ";
                        break;
                    case SegmentState::Damaged:
                        cout << " D ";
                        break;
                    case SegmentState::Destroyed:
                        cout << " ! ";
                        break;
                    default:
                        cout << "???";
                        break;
                }
            }
        }
        cout << "|" << endl;
    }

    cout << "  +";
    for (int x = 0; x < width; x++) {
        cout << "---"; // Consistent width for the bottom border
    }
    cout << "+" << endl;
}

// Get the status of a cell
CellStatus &GameBoard::getCellStatus(int x, int y) {
    if (y >= height || x >= width || x < 0 || y < 0) {
        throw out_of_range("Cell placement out of board bounds.");
    }
    return board[y][x];
}

void GameBoard::placeShipRandomly(Ship &ship) {
    int length = ship.getLength();
    
    if (length <= 0 || length > width && length > height) {
        throw std::invalid_argument("Invalid ship length");
    }

    bool isHorizontal = rand() % 2;
    int x, y;
    
    while (true) {
        if (isHorizontal) {
            x = rand() % (width - length + 1);
            y = rand() % height;
        } else {
            x = rand() % width;
            y = rand() % (height - length + 1);
        }

        bool canPlaceShip = true;
        for (int i = 0; i < length; ++i) {
            if (isHorizontal) {
                if (isOccupiedOrAdjacent(x + i, y)) {
                    canPlaceShip = false;
                    break;
                }
            } else {
                if (isOccupiedOrAdjacent(x, y + i)) {
                    canPlaceShip = false;
                    break;
                }
            }
        }

        if (canPlaceShip) {
            ship = Ship(length, isHorizontal, x, y);
            placeShip(ship, x, y, isHorizontal);
            return;
        }
    }
}

void to_json(json &j, const GameBoard &board)
{
    j = json{
        {"width", board.width},
        {"height", board.height},
        {"board", board.board}
    };
}

GameBoard::GameBoard(const json &j)
    : width(j["width"]), height(j["height"])
{
    board.resize(height, std::vector<CellStatus>(width, CellStatus(nullptr, 0, false)));

    int i = 0;
    for (auto &row : j["board"]) {
        int j = 0;
        for (auto &col : row) {
            board[i][j] = col;
            j++;
        }
        i++;
    }
}
