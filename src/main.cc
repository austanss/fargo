#include "exec/simulation.hh"
#include "exec/context.hh"
#include <iostream>
#include <memory>

using namespace fargo;

int main(int argc, char** argv) 
{
    Context context = Context();
    context.restore_defaults();
    
    if (context.match_parameters_raw(argc, argv).status != Status::FLAWLESS) {
        std::cout << "Failed to match (invalid) parameters. Exiting." << std::endl;
        return 1;
    }
    
    std::cout << "Independent variables: \n";
    std::cout << "\tBenefits: " << context.independents.benefits;
    std::cout << "\n\tRestrictions: " << context.independents.restricts;
    std::cout << "\n\tGradual: " << context.independents.gradually;
    std::cout << "\nControlled variables: \n";
    std::cout << "\tPopulation size: " << context.controls.pop_size;
    std::cout << "\n\tDuration (months): " << context.controls.max_months;
    std::cout << "\n\tMonthly benefit: " << context.controls.monthly_benefit << std::endl << std::endl;


    const std::string primary_label = "Simulation";
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(primary_label);
    sim->reset();

    // Used to externally observe if the loop is hung up
    int tick_indicator = 0;
    std::cout << "\nTick evidence: 0" << tick_indicator;

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
