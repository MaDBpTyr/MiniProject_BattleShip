#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Board.h"
#include "Stats.h"
#include "Strategy.h"

// Player gom ban cua minh, ban theo doi doi thu, thong ke va chien thuat.
class Player {
private:
    std::string name;
    Board ownBoard;
    Board trackingBoard;
    Strategy* strategy;
    PlayerStats stats;

    Position findFirstAvailableMove() const;

public:
    Player(std::string playerName, Strategy* playerStrategy);
    ~Player();

    // Khong cho copy Player vi Player dang so huu con tro Strategy*.
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    void resetForNewGame();
    void attack(Player& enemy);
    bool hasLost() const;

    std::string getName() const;
    std::string getStrategyName() const;
    PlayerStats getStats() const;
};

#endif
