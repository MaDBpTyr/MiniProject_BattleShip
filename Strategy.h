#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include "Board.h"

enum class StrategyType {
    Random,
    Checkerboard,
    HuntTarget
};

// Strategy la lop cha truu tuong.
// Moi chien thuat bot chi can cai dat chooseMove va getName.
class Strategy {
public:
    virtual ~Strategy() {}
    virtual Position chooseMove(const Board& knowledgeBoard) = 0;
    virtual std::string getName() const = 0;
    virtual void reset() {}
};

class RandomStrategy : public Strategy {
public:
    Position chooseMove(const Board& knowledgeBoard);
    std::string getName() const;
};

class CheckerboardStrategy : public Strategy {
public:
    Position chooseMove(const Board& knowledgeBoard);
    std::string getName() const;
};

class HuntTargetStrategy : public Strategy {
public:
    Position chooseMove(const Board& knowledgeBoard);
    std::string getName() const;
};

Strategy* createStrategy(StrategyType type);

#endif
