#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <stdexcept>
#include <memory>

using namespace std;

// States of the ship segment
enum class SegmentState {
    Intact,
    Damaged,
    Destroyed
};

enum class AttackResult {
    ShipDamaged,
    ShipDestroyed,
    Nothing
};

class Ship {
public:
    // Constructor for the ship
    Ship(int length, bool isHorizontal, int x, int y);

    // Get the length of the ship
    int getLength() const;

    // Check if the ship is horizontal
    bool isHorizontalOrientation() const;

    // Get the state of the segment by index
    SegmentState getSegmentState(int index) const;

    // Inflict damage on the segment
    AttackResult takeDamage(int index);

    int getX() const;
    int getY() const;

    int getSegmentIndex(int segX, int segY);

private:
    int length;                 // The length of the ship
    bool isHorizontal;          // Orientation (horizontal or vertical)
    int x, y;                   // The coordinates of the start of the ship
    vector<SegmentState> segments;  // The states of the ship segments
};

#endif // SHIP_H