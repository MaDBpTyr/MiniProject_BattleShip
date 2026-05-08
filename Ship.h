#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include "Position.h"

// Ship quan ly thong tin cua mot tau: ten, kich thuoc, so lan bi ban trung.
class Ship {
private:
    std::string name;
    int size;
    int hitCount;
    std::vector<Position> positions;

public:
    Ship();
    Ship(std::string shipName, int shipSize, std::vector<Position> shipPositions);

    std::string getName() const;
    int getSize() const;
    int getHitCount() const;
    std::vector<Position> getPositions() const;

    bool occupies(const Position& p) const;
    bool isSunk() const;
    void receiveHit();
};

#endif
