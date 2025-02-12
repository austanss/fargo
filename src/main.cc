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


    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(context);
    sim->reset();

    bool running = true;
    while (running) {
        Status latest_status = sim->update().status;
        running = !(StatusValidator::indicates_intervention(latest_status));
        if (latest_status == Status::ERROR_OUT_OF_TIME) {
            std::cout << "\nSimulation \"" << sim->get_label() << "\" finished as due." << std::endl;
            break;
        }
        if (!running) {
            std::cout << "\nSimulation \"" << sim->get_label() << "\" ended with status " << latest_status << "." << std::endl;
        }
    }

    return 0;
}
