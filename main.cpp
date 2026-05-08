#include <cstdlib>
#include <ctime>
#include "Simulation.h"

int main() {
    // Gieo seed de moi lan chay tau duoc dat ngau nhien khac nhau.
    srand((unsigned int)time(nullptr));

    // Mac dinh: so sanh Checkerboard voi Hunt & Target trong 10 tran.
    // Co the doi thanh StrategyType::Random de thu Random Strategy.
    Simulation simulation(StrategyType::Random, StrategyType::Random, 10);
    simulation.run10Games();

    return 0;
}
