#include "ship.h"
#include <memory>

// Constructor for the ship
Ship::Ship(int length, bool isHorizontal, int x, int y)
        : length(length), isHorizontal(isHorizontal), x(x), y(y) {
    if (length < 1 || length > 4) {
        throw invalid_argument("Ship length should be between 1 and 4.");
    }
    segments.resize(length, SegmentState::Intact);
}

// Returns the length of the ship
int Ship::getLength() const {
    return length;
}

// Checks if the ship is horizontal
bool Ship::isHorizontalOrientation() const {
    return isHorizontal;
}

int Ship::getX() const {
    return x;
}

int Ship::getY() const {
    return y;
}

// Returns the state of the segment by index
SegmentState Ship::getSegmentState(int index) const {
    if (index < 0 || index >= length) {
        throw out_of_range("Invalid segment index.");
    }
    return segments[index];
}

// Inflicts damage on the ship segment
AttackResult Ship::takeDamage(int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("Invalid segment index.");
    }

    if (segments[index] == SegmentState::Intact) {
        segments[index] = SegmentState::Damaged;
        return AttackResult::ShipDamaged;
    }

    if (segments[index] == SegmentState::Damaged) {
        segments[index] = SegmentState::Destroyed;

        for (int i = 0; i < length; i++) {
            if (segments[i] != SegmentState::Destroyed) {
                return AttackResult::ShipDamaged;
            }
        }
        return AttackResult::ShipDestroyed;
    }

    return AttackResult::Nothing;
}

// Gets the segment index based on coordinates
int Ship::getSegmentIndex(int segX, int segY) {
    if(isHorizontal) {
        return segX - x;
    } else {
        return segY - y;
    }
}