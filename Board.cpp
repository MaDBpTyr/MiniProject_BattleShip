#include "Board.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

Board::Board() {
    reset();
}

void Board::clearGrid() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            grid[r][c] = CellState::Empty;
        }
    }
}

void Board::reset() {
    clearGrid();
    ships.clear();
}

bool Board::isInside(const Position& p) const {
    return p.isValid();
}

CellState Board::getCell(const Position& p) const {
    if (!isInside(p)) {
        return CellState::Empty;
    }
    return grid[p.row][p.col];
}

bool Board::hasBeenShot(const Position& p) const {
    CellState state = getCell(p);
    return state == CellState::Hit || state == CellState::Miss || state == CellState::Sunk;
}

bool Board::canPlaceShip(const Position& start, int shipSize, bool horizontal) const {
    for (int i = 0; i < shipSize; i++) {
        int r = start.row;
        int c = start.col;

        if (horizontal) {
            c += i;
        } else {
            r += i;
        }

        Position p(r, c);
        if (!isInside(p) || grid[r][c] != CellState::Empty) {
            return false;
        }
    }
    return true;
}

void Board::placeShipsRandom() {
    reset();

    string names[5] = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};
    int sizes[5] = {2, 3, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        bool placed = false;

        while (!placed) {
            Position start(rand() % BOARD_SIZE, rand() % BOARD_SIZE);
            bool horizontal = (rand() % 2 == 0);

            if (canPlaceShip(start, sizes[i], horizontal)) {
                vector<Position> shipPositions;

                for (int j = 0; j < sizes[i]; j++) {
                    int r = start.row;
                    int c = start.col;

                    if (horizontal) {
                        c += j;
                    } else {
                        r += j;
                    }

                    grid[r][c] = CellState::Ship;
                    shipPositions.push_back(Position(r, c));
                }

                ships.push_back(Ship(names[i], sizes[i], shipPositions));
                placed = true;
            }
        }
    }
}

AttackResult Board::receiveAttack(const Position& p) {
    if (!isInside(p)) {
        return AttackResult(AttackType::Invalid);
    }

    CellState& cell = grid[p.row][p.col];

    if (cell == CellState::Miss || cell == CellState::Hit || cell == CellState::Sunk) {
        return AttackResult(AttackType::AlreadyShot);
    }

    if (cell == CellState::Empty) {
        cell = CellState::Miss;
        return AttackResult(AttackType::Miss);
    }

    // Neu o dang co tau, tim tau nao nam tai vi tri nay.
    if (cell == CellState::Ship) {
        cell = CellState::Hit;

        for (int i = 0; i < (int)ships.size(); i++) {
            if (ships[i].occupies(p)) {
                ships[i].receiveHit();

                if (ships[i].isSunk()) {
                    vector<Position> sunkPositions = ships[i].getPositions();

                    for (int j = 0; j < (int)sunkPositions.size(); j++) {
                        Position shipCell = sunkPositions[j];
                        grid[shipCell.row][shipCell.col] = CellState::Sunk;
                    }

                    AttackResult result(AttackType::Sunk, ships[i].getName());
                    result.sunkPositions = sunkPositions;
                    return result;
                }

                return AttackResult(AttackType::Hit, ships[i].getName());
            }
        }
    }

    return AttackResult(AttackType::Miss);
}

void Board::markAttackResult(const Position& p, const AttackResult& result) {
    if (!isInside(p)) {
        return;
    }

    if (result.type == AttackType::Miss) {
        grid[p.row][p.col] = CellState::Miss;
    } else if (result.type == AttackType::Hit) {
        grid[p.row][p.col] = CellState::Hit;
    } else if (result.type == AttackType::Sunk) {
        if (result.sunkPositions.empty()) {
            grid[p.row][p.col] = CellState::Sunk;
        } else {
            for (int i = 0; i < (int)result.sunkPositions.size(); i++) {
                Position shipCell = result.sunkPositions[i];
                if (isInside(shipCell)) {
                    grid[shipCell.row][shipCell.col] = CellState::Sunk;
                }
            }
        }
    }
}

bool Board::allShipsSunk() const {
    if (ships.empty()) {
        return false;
    }

    for (int i = 0; i < (int)ships.size(); i++) {
        if (!ships[i].isSunk()) {
            return false;
        }
    }
    return true;
}

void Board::displayBoard(bool showShips) const {
    cout << "   ";
    for (int c = 0; c < BOARD_SIZE; c++) {
        cout << setw(2) << c << " ";
    }
    cout << endl;

    for (int r = 0; r < BOARD_SIZE; r++) {
        cout << setw(2) << r << " ";

        for (int c = 0; c < BOARD_SIZE; c++) {
            char symbol = '.';

            if (grid[r][c] == CellState::Ship && showShips) {
                symbol = 'S';
            } else if (grid[r][c] == CellState::Hit) {
                symbol = 'X';
            } else if (grid[r][c] == CellState::Miss) {
                symbol = 'o';
            } else if (grid[r][c] == CellState::Sunk) {
                symbol = '#';
            }

            cout << " " << symbol << " ";
        }
        cout << endl;
    }
}
