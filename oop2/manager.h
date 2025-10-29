#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <memory>
#include "ship.h"
using namespace std;

class ShipManager {
public:
    // Constructor with number and types of ships
    ShipManager(int numShips, vector<Ship> &usedShips);

    // Returns the number of alive ships
    int getNumAliveShips() const;
    int getNumShips() const;
    // Returns the index of the ship by coordinates x and y, or -1 if not found
    int getShipInd(int x, int y) const;

    // Inflicts damage on the ship by index
    void takeDamageByIndex(int shipIndex, int x, int y);

    typedef vector<Ship>::iterator iterator;

    iterator begin() { return ships.begin(); }
    iterator end() { return ships.end(); }

private:
    vector<Ship> ships;
};

#endif // SHIPMANAGER_H