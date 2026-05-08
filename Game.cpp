#include "Game.h"

Game::Game(std::string bot1Name, Strategy* bot1Strategy,
           std::string bot2Name, Strategy* bot2Strategy)
    : bot1(bot1Name, bot1Strategy), bot2(bot2Name, bot2Strategy) {
}

void Game::resetGame() {
    bot1.resetForNewGame();
    bot2.resetForNewGame();
}

GameResult Game::playOneGame(int gameNumber) {
    resetGame();

    // Doi bot bat dau theo so tran de giam loi the di truoc.
    bool bot1Turn = (gameNumber % 2 == 1);

    while (!bot1.hasLost() && !bot2.hasLost()) {
        if (bot1Turn) {
            bot1.attack(bot2);
        } else {
            bot2.attack(bot1);
        }
        bot1Turn = !bot1Turn;
    }

    GameResult result;
    result.bot1Name = bot1.getName();
    result.bot2Name = bot2.getName();
    result.bot1Strategy = bot1.getStrategyName();
    result.bot2Strategy = bot2.getStrategyName();
    result.bot1Stats = bot1.getStats();
    result.bot2Stats = bot2.getStats();

    if (bot1.hasLost()) {
        result.winnerName = bot2.getName();
    } else {
        result.winnerName = bot1.getName();
    }

    return result;
}
