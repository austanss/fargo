#include "exec/simulation.hh"
#include <iostream>
#include <thread>

using namespace fargo;

Simulation::Simulation(const Context params) : parameters(params)
{
    this->state.active = false;
    this->label = std::string(parameters.environment.output_label);
    this->population = std::make_unique<Population>();

    std::cout << "Initiated new simulation \"" << this->label << "\"." << std::endl;
}

Simulation::~Simulation()
{
    // Hay nada que hacer ahora
}

Simulation::Simulation() {}

Response<void> Simulation::reset()
{
    Status latest_status = Status::FLAWLESS;
    this->state.active = true;
    this->state.month_tick = 0;

    latest_status = this->population->reset().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        this->state.active = false;
        return Response<void>(latest_status);
    }

    std::cout << "Simulation \"" << this->label << "\" reset to default state." << std::endl;

    return Responses::flawless();
}

Response<void> Simulation::update()
{
    if (!this->state.active) {
        return Response<void>(Status::QUIET_FAILURE);
    }

    Status latest_status = Status::FLAWLESS;

    latest_status = this->population->update().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        this->state.active = false;
        return Response<void>(latest_status);
    }

    this->state.month_tick++;

    if (this->state.month_tick > this->parameters.controls.max_months) {
        this->state.active = false;
        return Response<void>(Status::ERROR_OUT_OF_TIME);
    }

    return latest_status;
}
