#include "Strategy.h"
#include <cstdlib>
#include <vector>

using namespace std;

static bool containsPosition(const vector<Position>& positions, const Position& p) {
    for (int i = 0; i < (int)positions.size(); i++) {
        if (positions[i].equals(p)) {
            return true;
        }
    }
    return false;
}

static void addCandidate(const Board& board, vector<Position>& candidates, const Position& p) {
    if (p.isValid() && !board.hasBeenShot(p) && !containsPosition(candidates, p)) {
        candidates.push_back(p);
    }
}

static Position chooseRandomCell(const vector<Position>& candidates) {
    if (candidates.empty()) {
        return Position(-1, -1);
    }
    int index = rand() % candidates.size();
    return candidates[index];
}

static vector<Position> collectAllUnshotCells(const Board& board) {
    vector<Position> cells;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Position p(r, c);
            if (!board.hasBeenShot(p)) {
                cells.push_back(p);
            }
        }
    }

    return cells;
}

static vector<Position> collectCheckerboardCells(const Board& board) {
    vector<Position> cells;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Position p(r, c);
            if ((r + c) % 2 == 0 && !board.hasBeenShot(p)) {
                cells.push_back(p);
            }
        }
    }

    return cells;
}

static Position chooseHuntMove(const Board& board) {
    vector<Position> checkerCells = collectCheckerboardCells(board);
    if (!checkerCells.empty()) {
        return chooseRandomCell(checkerCells);
    }

    return chooseRandomCell(collectAllUnshotCells(board));
}

Position RandomStrategy::chooseMove(const Board& knowledgeBoard) {
    return chooseRandomCell(collectAllUnshotCells(knowledgeBoard));
}

string RandomStrategy::getName() const {
    return "Random Strategy";
}

Position CheckerboardStrategy::chooseMove(const Board& knowledgeBoard) {
    return chooseHuntMove(knowledgeBoard);
}

string CheckerboardStrategy::getName() const {
    return "Checkerboard Strategy";
}

Position HuntTargetStrategy::chooseMove(const Board& knowledgeBoard) {
    vector<Position> hitCells;

    // Tim cac o da HIT nhung chua SUNK de chuyen sang Target mode.
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Position p(r, c);
            if (knowledgeBoard.getCell(p) == CellState::Hit) {
                hitCells.push_back(p);
            }
        }
    }

    if (!hitCells.empty()) {
        vector<Position> targetCandidates;

        // Neu co tu 2 o HIT nam thang hang, uu tien ban tiep theo cung huong.
        if ((int)hitCells.size() >= 2) {
            bool sameRow = true;
            bool sameCol = true;

            for (int i = 1; i < (int)hitCells.size(); i++) {
                if (hitCells[i].row != hitCells[0].row) {
                    sameRow = false;
                }
                if (hitCells[i].col != hitCells[0].col) {
                    sameCol = false;
                }
            }

            if (sameRow) {
                int row = hitCells[0].row;
                int minCol = hitCells[0].col;
                int maxCol = hitCells[0].col;

                for (int i = 1; i < (int)hitCells.size(); i++) {
                    if (hitCells[i].col < minCol) {
                        minCol = hitCells[i].col;
                    }
                    if (hitCells[i].col > maxCol) {
                        maxCol = hitCells[i].col;
                    }
                }

                addCandidate(knowledgeBoard, targetCandidates, Position(row, minCol - 1));
                addCandidate(knowledgeBoard, targetCandidates, Position(row, maxCol + 1));
            }

            if (targetCandidates.empty() && sameCol) {
                int col = hitCells[0].col;
                int minRow = hitCells[0].row;
                int maxRow = hitCells[0].row;

                for (int i = 1; i < (int)hitCells.size(); i++) {
                    if (hitCells[i].row < minRow) {
                        minRow = hitCells[i].row;
                    }
                    if (hitCells[i].row > maxRow) {
                        maxRow = hitCells[i].row;
                    }
                }

                addCandidate(knowledgeBoard, targetCandidates, Position(minRow - 1, col));
                addCandidate(knowledgeBoard, targetCandidates, Position(maxRow + 1, col));
            }
        }

        // Neu moi co 1 HIT hoac chua xac dinh duoc huong, thu 4 o xung quanh.
        if (targetCandidates.empty()) {
            for (int i = 0; i < (int)hitCells.size(); i++) {
                Position h = hitCells[i];
                addCandidate(knowledgeBoard, targetCandidates, Position(h.row - 1, h.col));
                addCandidate(knowledgeBoard, targetCandidates, Position(h.row + 1, h.col));
                addCandidate(knowledgeBoard, targetCandidates, Position(h.row, h.col - 1));
                addCandidate(knowledgeBoard, targetCandidates, Position(h.row, h.col + 1));
            }
        }

        if (!targetCandidates.empty()) {
            return chooseRandomCell(targetCandidates);
        }
    }

    // Hunt mode: neu chua co HIT nao thi di theo mau caro.
    return chooseHuntMove(knowledgeBoard);
}

string HuntTargetStrategy::getName() const {
    return "Hunt & Target Strategy";
}

Strategy* createStrategy(StrategyType type) {
    if (type == StrategyType::Random) {
        return new RandomStrategy();
    }
    if (type == StrategyType::Checkerboard) {
        return new CheckerboardStrategy();
    }
    return new HuntTargetStrategy();
}
