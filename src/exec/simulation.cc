#include "exec/simulation.hh"
#include "response.hh"
#include <iostream>

using namespace fargo;

Simulation::Simulation(const bool start_graphic, const std::string& new_label)
{
    this->currently.is_running = false;
    this->currently.is_graphical = (bool)start_graphic;
    this->label = std::string(new_label);

    if (this->currently.is_graphical) {
        this->canvas = std::make_unique<Visualizer>();
    }

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

    latest_status = this->population->reset().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        return Response<void>(latest_status);
    }

    if (this->currently.is_graphical) {
        latest_status = this->canvas->reset(this->label).status;
        if (StatusValidator::indicates_intervention(latest_status)) {
            this->currently.is_graphical = false;
            latest_status = this->canvas->cancel().status;
            if (latest_status == Status::REDUNDANT) {
                return Response<void>(Status::ERROR_STATE_CORRUPT);
            }
        }
    }

    this->currently.is_running = true;

    std::cout << "Simulation \"" << this->label << "\" reset to default state." << std::endl;

    return Responses::flawless();
}

Response<void> Simulation::update()
{
    if (!this->currently.is_running) {
        return Response<void>(Status::QUIET_FAILURE);
    }

    Status latest_status = Status::FLAWLESS;

    if (this->currently.is_graphical) {
        latest_status = this->canvas->update_with(this->population->reference_data()).status;
        if (StatusValidator::indicates_intervention(latest_status)) {
            this->currently.is_graphical = false;
            latest_status = this->canvas->cancel().status;
            if (latest_status == Status::REDUNDANT) {
                return Response<void>(Status::ERROR_STATE_CORRUPT);
            }
        }
    }

    latest_status = this->population->update().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        this->currently.is_running = false;
        return Response<void>(latest_status);
    }

    this->currently.month_tick++;

    return latest_status;
}
