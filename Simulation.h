#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "Game.h"
#include "Stats.h"
#include "Strategy.h"

struct SimulationSummary {
    int totalGames;
    int bot1Wins;
    int bot2Wins;
    PlayerStats bot1Total;
    PlayerStats bot2Total;
};

// Simulation chay nhieu tran, luu thong ke va in bao cao.
class Simulation {
private:
    StrategyType bot1StrategyType;
    StrategyType bot2StrategyType;
    int totalGames;
    std::vector<GameResult> results;

    void printGameResult(int gameNumber, const GameResult& result) const;
    std::string chooseBestStrategy(const SimulationSummary& summary) const;
    std::string chooseWorstStrategy(const SimulationSummary& summary) const;
    std::string buildComment(const SimulationSummary& summary) const;

public:
    Simulation(StrategyType strategy1, StrategyType strategy2, int games = 10);

    void run10Games();
    SimulationSummary collectStatistics() const;
    void printReport() const;
};

#endif
