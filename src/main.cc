#include "exec/simulation.hh"
#include <iostream>
#include <memory>

using namespace fargo;

int main(int argc, char** argv) 
{
    const std::string primary_label = "Simulation";
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(true, primary_label);
    sim->reset();

    // Used to externally observe if the loop is hung up
    int tick_indicator = 0;
    std::cout << "Tick evidence: 0" << tick_indicator;

    bool running = true;
    while (running) {
        Status latest_status = sim->update().status;
        running = !(StatusValidator::indicates_intervention(latest_status));
        if (!running) {
            std::cout << "Simulation '" << sim->get_label() << "' ended with status " << latest_status << "." << std::endl;
        }

        std::cout << "\b\b" << ((tick_indicator < 10) ? "0" : "") << tick_indicator++;
        if (tick_indicator > 99) {
            tick_indicator = 0;
        }
    }

    return 0;
}
