#include "Simulation.h"
#include <iomanip>
#include <iostream>

using namespace std;

Simulation::Simulation(StrategyType strategy1, StrategyType strategy2, int games) {
    bot1StrategyType = strategy1;
    bot2StrategyType = strategy2;
    totalGames = games;
}

void Simulation::run10Games() {
    results.clear();

    Game game("Bot A", createStrategy(bot1StrategyType),
              "Bot B", createStrategy(bot2StrategyType));

    for (int i = 1; i <= totalGames; i++) {
        GameResult result = game.playOneGame(i);
        results.push_back(result);
        printGameResult(i, result);
    }

    printReport();
}

void Simulation::printGameResult(int gameNumber, const GameResult& result) const {
    cout << "===== GAME " << gameNumber << " =====" << endl;
    cout << result.bot1Name << " Strategy: " << result.bot1Strategy << endl;
    cout << result.bot2Name << " Strategy: " << result.bot2Strategy << endl;
    cout << "Winner: " << result.winnerName << endl;

    cout << result.bot1Name << " shots: " << result.bot1Stats.shots
         << ", hits: " << result.bot1Stats.hits
         << ", misses: " << result.bot1Stats.misses
         << ", ships sunk: " << result.bot1Stats.shipsSunk
         << ", hit rate: " << fixed << setprecision(2) << result.bot1Stats.hitRate() << "%" << endl;

    cout << result.bot2Name << " shots: " << result.bot2Stats.shots
         << ", hits: " << result.bot2Stats.hits
         << ", misses: " << result.bot2Stats.misses
         << ", ships sunk: " << result.bot2Stats.shipsSunk
         << ", hit rate: " << fixed << setprecision(2) << result.bot2Stats.hitRate() << "%" << endl;
    cout << endl;
}

SimulationSummary Simulation::collectStatistics() const {
    SimulationSummary summary;
    summary.totalGames = (int)results.size();
    summary.bot1Wins = 0;
    summary.bot2Wins = 0;
    summary.bot1Total.reset();
    summary.bot2Total.reset();

    for (int i = 0; i < (int)results.size(); i++) {
        if (results[i].winnerName == results[i].bot1Name) {
            summary.bot1Wins++;
        } else {
            summary.bot2Wins++;
        }

        addStats(summary.bot1Total, results[i].bot1Stats);
        addStats(summary.bot2Total, results[i].bot2Stats);
    }

    return summary;
}

string Simulation::chooseBestStrategy(const SimulationSummary& summary) const {
    if (results.empty()) {
        return "No data";
    }

    if (summary.bot1Wins > summary.bot2Wins) {
        return results[0].bot1Strategy;
    }
    if (summary.bot2Wins > summary.bot1Wins) {
        return results[0].bot2Strategy;
    }

    double avgShots1 = (double)summary.bot1Total.shots / summary.totalGames;
    double avgShots2 = (double)summary.bot2Total.shots / summary.totalGames;

    if (avgShots1 < avgShots2) {
        return results[0].bot1Strategy;
    }
    if (avgShots2 < avgShots1) {
        return results[0].bot2Strategy;
    }

    return "Tie";
}

string Simulation::chooseWorstStrategy(const SimulationSummary& summary) const {
    if (results.empty()) {
        return "No data";
    }

    string best = chooseBestStrategy(summary);

    if (best == results[0].bot1Strategy) {
        return results[0].bot2Strategy;
    }
    if (best == results[0].bot2Strategy) {
        return results[0].bot1Strategy;
    }
    return "Tie";
}

string Simulation::buildComment(const SimulationSummary& summary) const {
    string best = chooseBestStrategy(summary);

    if (best == "Hunt & Target Strategy") {
        return "Hunt & Target hieu qua hon vi sau khi ban trung, bot tap trung ban cac o xung quanh va mo rong theo dung huong de danh chim tau nhanh hon.";
    }
    if (best == "Checkerboard Strategy") {
        return "Checkerboard hieu qua vi bot giam so o can thu trong giai doan tim tau, dac biet khi tau nho nhat co kich thuoc 2.";
    }
    if (best == "Random Strategy") {
        return "Random co the thang trong mot so tran do may man, nhung ve lau dai thuong kem on dinh hon cac chien thuat co mau tim kiem.";
    }
    return "Hai chien thuat dang co ket qua kha can bang trong 10 tran; nen tang so tran neu muon so sanh chinh xac hon.";
}

void Simulation::printReport() const {
    SimulationSummary summary = collectStatistics();

    if (summary.totalGames == 0) {
        cout << "No game data." << endl;
        return;
    }

    double bot1WinRate = (double)summary.bot1Wins * 100.0 / summary.totalGames;
    double bot2WinRate = (double)summary.bot2Wins * 100.0 / summary.totalGames;
    double avgShots1 = (double)summary.bot1Total.shots / summary.totalGames;
    double avgShots2 = (double)summary.bot2Total.shots / summary.totalGames;

    cout << "===== FINAL REPORT =====" << endl;
    cout << "Total games: " << summary.totalGames << endl;
    cout << results[0].bot1Name << " wins: " << summary.bot1Wins
         << " (" << fixed << setprecision(2) << bot1WinRate << "%)" << endl;
    cout << results[0].bot2Name << " wins: " << summary.bot2Wins
         << " (" << fixed << setprecision(2) << bot2WinRate << "%)" << endl;
    if (summary.bot1Wins > summary.bot2Wins) {
        cout << "Overall winner: " << results[0].bot1Name << endl;
    } else if (summary.bot2Wins > summary.bot1Wins) {
        cout << "Overall winner: " << results[0].bot2Name << endl;
    } else {
        cout << "Overall winner: Tie" << endl;
    }
    cout << endl;

    cout << "Total shots " << results[0].bot1Name << ": " << summary.bot1Total.shots << endl;
    cout << "Total shots " << results[0].bot2Name << ": " << summary.bot2Total.shots << endl;
    cout << "Average shots " << results[0].bot1Name << ": " << fixed << setprecision(2) << avgShots1 << endl;
    cout << "Average shots " << results[0].bot2Name << ": " << fixed << setprecision(2) << avgShots2 << endl;
    cout << endl;

    cout << "Total HIT/MISS " << results[0].bot1Name << ": "
         << summary.bot1Total.hits << "/" << summary.bot1Total.misses << endl;
    cout << "Total HIT/MISS " << results[0].bot2Name << ": "
         << summary.bot2Total.hits << "/" << summary.bot2Total.misses << endl;
    cout << "Hit rate " << results[0].bot1Name << ": " << fixed << setprecision(2)
         << summary.bot1Total.hitRate() << "%" << endl;
    cout << "Hit rate " << results[0].bot2Name << ": " << fixed << setprecision(2)
         << summary.bot2Total.hitRate() << "%" << endl;
    cout << endl;

    cout << "Best strategy: " << chooseBestStrategy(summary) << endl;
    cout << "Weakest strategy: " << chooseWorstStrategy(summary) << endl;
    cout << "Comment: " << buildComment(summary) << endl;
    cout << endl;

    cout << "Conclusion:" << endl;
    cout << "Neu la nguoi choi, nen ket hop Checkerboard de tim tau va Hunt & Target de danh chim tau sau khi HIT." << endl;
    cout << "Neu la quan ly game, nen quan ly ro luat ban, tranh ban trung o, luu thong ke moi tran va so sanh chien thuat bang win rate, average shots va hit rate." << endl;
}
