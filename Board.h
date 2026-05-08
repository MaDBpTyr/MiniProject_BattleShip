#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "AttackResult.h"
#include "Constants.h"
#include "Ship.h"

// Board quan ly ban choi 10x10 va danh sach tau.
class Board {
private:
    CellState grid[BOARD_SIZE][BOARD_SIZE];
    std::vector<Ship> ships;

    void clearGrid();

public:
    Board();

    void reset();
    bool isInside(const Position& p) const;
    CellState getCell(const Position& p) const;
    bool hasBeenShot(const Position& p) const;

    bool canPlaceShip(const Position& start, int shipSize, bool horizontal) const;
    void placeShipsRandom();

    AttackResult receiveAttack(const Position& p);
    void markAttackResult(const Position& p, const AttackResult& result);

    bool allShipsSunk() const;
    void displayBoard(bool showShips) const;
};

#endif
