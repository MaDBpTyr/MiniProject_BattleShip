#ifndef ATTACK_RESULT_H
#define ATTACK_RESULT_H

#include <string>
#include <vector>
#include "Position.h"

// Trang thai tung o tren ban.
enum class CellState {
    Empty,  // Chua co gi / chua ban
    Ship,   // Co tau, chi hien tren ban cua chinh nguoi choi
    Hit,    // Da ban trung
    Miss,   // Da ban truot
    Sunk    // O thuoc tau da bi danh chim
};

// Ket qua cua mot lan ban.
enum class AttackType {
    Miss,
    Hit,
    Sunk,
    AlreadyShot,
    Invalid
};

// AttackResult gom ket qua va thong tin tau bi chim neu co.
struct AttackResult {
    AttackType type;
    std::string shipName;
    std::vector<Position> sunkPositions;

    AttackResult(AttackType t = AttackType::Miss, std::string name = "") {
        type = t;
        shipName = name;
    }
};

#endif
