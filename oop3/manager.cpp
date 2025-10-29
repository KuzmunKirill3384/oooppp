#include "manager.h"

using namespace std;

ShipManager::ShipManager(vector<int> &shipSizes)
{
    for (int i = 0; i < shipSizes.size(); i++) {
        for (int j = 0; j < shipSizes[i]; j++) {
            ships.push_back(Ship(i + 1, false, 0, 0));
        } 
    }
}

int ShipManager::getNumAliveShips() const {
    int aliveCount = 0;
    for (const auto & ship : ships) {
        bool isDead = true;
        for (int j = 0; j < ship.getLength(); j++){
            SegmentState status = ship.getSegmentState(j);
            if (status == SegmentState::Intact || status == SegmentState::Damaged) {
                isDead = false;
            }
        }
        if (!isDead) {
            aliveCount++;
        }
    }
    return aliveCount;
}

int ShipManager::getNumShips() const {
    return ships.size();
}

int ShipManager::getShipInd(int x, int y) const {
    for (int i = 0; i < ships.size(); i++) {
        int shipX = ships[i].getX();
        int shipY = ships[i].getY();
        int length = ships[i].getLength();
        bool isHorizontal = ships[i].isHorizontalOrientation();

        // Check vertical orientation
        if (!isHorizontal && shipX == x && y >= shipY && y <= shipY + length - 1) {
            return i;
        }
            // Check horizontal orientation
        else if (isHorizontal && shipY == y && x >= shipX && x <= shipX + length - 1) {
            return i;
        }
    }
    return -1;  // Ship not found
}

void ShipManager::takeDamageByIndex(int shipIndex, int x, int y) {
    if (shipIndex >= 0 && shipIndex < ships.size()) {
        int segmentIndex = ships[shipIndex].getSegmentIndex(x, y);
        ships[shipIndex].takeDamage(segmentIndex);
    }
}

void to_json(json &j, const ShipManager &manager)
{
    j = json{{"ships", manager.ships}};
}

ShipManager::ShipManager(const json &j)
{
    for (const auto &ship_json : j["ships"]) {
        ships.push_back(ship_json);
    }
}
