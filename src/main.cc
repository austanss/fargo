#include <memory>
#include <minifb/minifb.h>
#include "exec/simulation.hh"

using namespace fargo;

int main() {
    std::unique_ptr<Simulation> sim_main = std::make_unique<Simulation>("Main");

    sim_main->reset(true);

    while (sim_main->is_valid()) {
        sim_main->tick();
    }
}
