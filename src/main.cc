#include "exec/simulation.hh"
#include <iostream>
#include <memory>

using namespace fargo;

int main(int argc, char** argv) 
{
    const std::string primary_label = "Simulation";
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(true, primary_label);
    sim->reset();

    // Used to ensure that the loop is not hung up
    int tick_indicator = 0;
    std::cout << "Tick evidence: " << tick_indicator;
    
    bool running = true;
    while (running) {
        Status current_status = sim->update().status;
        running = !(StatusChecker::indicates_intervention(current_status));
        if (!running) {
            std::cout << "Simulation '" << sim->get_label() << "' ended with status " << current_status << "." << std::endl;
        }

        std::cout << '\b' << tick_indicator++;
        if (tick_indicator > 9) {
            tick_indicator = 0;
        }
    }

    // Redundant reassurance
    sim.release();

    return 0;
}
