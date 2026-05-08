#ifndef POSITION_H
#define POSITION_H

#include "Constants.h"

// Position dai dien cho mot toa do tren ban co.
struct Position {
    int row;
    int col;

    Position(int r = 0, int c = 0) {
        row = r;
        col = c;
    }

    bool isValid() const {
        return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
    }

    bool equals(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

#endif
