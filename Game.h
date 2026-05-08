#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Stats.h"

// Game dieu khien mot tran dau giua 2 bot.
class Game {
private:
    Player bot1;
    Player bot2;

public:
    Game(std::string bot1Name, Strategy* bot1Strategy,
         std::string bot2Name, Strategy* bot2Strategy);

    void resetGame();
    GameResult playOneGame(int gameNumber);
};

#endif
