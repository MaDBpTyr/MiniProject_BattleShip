#include "Ship.h"

Ship::Ship() {
    name = "";
    size = 0;
    hitCount = 0;
}

Ship::Ship(std::string shipName, int shipSize, std::vector<Position> shipPositions) {
    name = shipName;
    size = shipSize;
    hitCount = 0;
    positions = shipPositions;
}

std::string Ship::getName() const {
    return name;
}

int Ship::getSize() const {
    return size;
}

int Ship::getHitCount() const {
    return hitCount;
}

std::vector<Position> Ship::getPositions() const {
    return positions;
}

bool Ship::occupies(const Position& p) const {
    for (int i = 0; i < (int)positions.size(); i++) {
        if (positions[i].equals(p)) {
            return true;
        }
    }
    return false;
}

bool Ship::isSunk() const {
    return hitCount >= size;
}

void Ship::receiveHit() {
    if (hitCount < size) {
        hitCount++;
    }
}
