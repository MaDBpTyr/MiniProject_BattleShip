#ifndef STATS_H
#define STATS_H

#include <string>

// Thong ke cua mot bot trong mot tran hoac nhieu tran.
struct PlayerStats {
    int shots;
    int hits;
    int misses;
    int shipsSunk;

    PlayerStats() {
        reset();
    }

    void reset() {
        shots = 0;
        hits = 0;
        misses = 0;
        shipsSunk = 0;
    }

    double hitRate() const {
        if (shots == 0) {
            return 0.0;
        }
        return (double)hits * 100.0 / shots;
    }
};

inline void addStats(PlayerStats& total, const PlayerStats& current) {
    total.shots += current.shots;
    total.hits += current.hits;
    total.misses += current.misses;
    total.shipsSunk += current.shipsSunk;
}

// Ket qua tom tat cua mot tran dau.
struct GameResult {
    std::string winnerName;
    std::string bot1Name;
    std::string bot2Name;
    std::string bot1Strategy;
    std::string bot2Strategy;
    PlayerStats bot1Stats;
    PlayerStats bot2Stats;
};

#endif
