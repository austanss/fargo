#include <memory>
#include <minifb/minifb.h>
#include "exec/simulation.hh"
#include "data/individual.hh"

using namespace fargo;

int main() {
    std::unique_ptr<SimulationHandle> sim_main = std::make_unique<SimulationHandle>("Main");

    sim_main->reset(true);

    while (sim_main->is_valid()) {
        sim_main->tick();
    }

    // Redundant
    sim_main.release();
}
