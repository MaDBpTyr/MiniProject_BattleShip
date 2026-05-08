#include "Player.h"

Player::Player(std::string playerName, Strategy* playerStrategy) {
    name = playerName;
    strategy = playerStrategy;
}

Player::~Player() {
    delete strategy;
    strategy = nullptr;
}

Position Player::findFirstAvailableMove() const {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            Position p(r, c);
            if (!trackingBoard.hasBeenShot(p)) {
                return p;
            }
        }
    }
    return Position(-1, -1);
}

void Player::resetForNewGame() {
    ownBoard.placeShipsRandom();
    trackingBoard.reset();
    stats.reset();

    if (strategy != nullptr) {
        strategy->reset();
    }
}

void Player::attack(Player& enemy) {
    if (strategy == nullptr) {
        return;
    }

    // Da hinh nam o dong nay: Player khong can biet strategy cu the la loai nao.
    Position shot = strategy->chooseMove(trackingBoard);

    if (!shot.isValid() || trackingBoard.hasBeenShot(shot)) {
        shot = findFirstAvailableMove();
    }

    if (!shot.isValid()) {
        return;
    }

    AttackResult result = enemy.ownBoard.receiveAttack(shot);

    // Neu gap loi logic hiem gap, fallback de dam bao khong tinh trung o.
    if (result.type == AttackType::AlreadyShot || result.type == AttackType::Invalid) {
        shot = findFirstAvailableMove();
        if (!shot.isValid()) {
            return;
        }
        result = enemy.ownBoard.receiveAttack(shot);
    }

    trackingBoard.markAttackResult(shot, result);

    stats.shots++;
    if (result.type == AttackType::Hit) {
        stats.hits++;
    } else if (result.type == AttackType::Sunk) {
        stats.hits++;
        stats.shipsSunk++;
    } else if (result.type == AttackType::Miss) {
        stats.misses++;
    }
}

bool Player::hasLost() const {
    return ownBoard.allShipsSunk();
}

std::string Player::getName() const {
    return name;
}

std::string Player::getStrategyName() const {
    if (strategy == nullptr) {
        return "No Strategy";
    }
    return strategy->getName();
}

PlayerStats Player::getStats() const {
    return stats;
}
