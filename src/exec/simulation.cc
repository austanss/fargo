#include "exec/simulation.hh"
#include "exec/response.hh"
#include <iostream>

using namespace fargo;

Simulation::Simulation(const bool enable_graphic, const std::string& new_label)
{
    this->is_graphical = (bool)enable_graphic;
    this->label = std::string(new_label);

    if (this->is_graphical) {
        this->canvas = std::make_unique<Visualizer>();
    }
    std::cout << "Initiated new simulation \"" << this->label << "\"." << std::endl;
}

Simulation::~Simulation()
{
    // Hay nada que hacer ahora
}

Simulation::Simulation() {}

Response<void> Simulation::reset()
{
    Status current_status = Status::FLAWLESS;

    if (this->is_graphical) {
        current_status = this->canvas->reset(this->label).status;
        if (StatusChecker::indicates_intervention(current_status)) {
            this->is_graphical = false;
            current_status = this->canvas->cancel().status;
            if (current_status == Status::REDUNDANT) {
                return Response<void>(Status::ERROR_STATE_CORRUPT);
            }
        }
    }

    return Responses::flawless();
}

Response<void> Simulation::update()
{
    Status current_status = Status::FLAWLESS;

    if (this->is_graphical) {
        current_status = this->canvas->update().status;
        if (StatusChecker::indicates_intervention(current_status)) {
            this->is_graphical = false;
            current_status = this->canvas->cancel().status;
            if (current_status == Status::REDUNDANT) {
                return Response<void>(Status::ERROR_STATE_CORRUPT);
            }
        }
    }

    return current_status;
}
