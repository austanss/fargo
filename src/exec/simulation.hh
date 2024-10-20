#pragma once
#include <string>
#include <memory>
#include "response.hh"
#include "gfx/visualizer.hh"
#include "data/population.hh"

namespace fargo 
{
    class Simulation
    {

    public:
        Simulation(const bool start_graphic, const std::string& new_label);
        ~Simulation();

        Response<void> reset();
        Response<void> update();

        inline const std::string& get_label() const { return this->label; }

    private:
        Simulation();

        struct {
            bool                is_running;
            bool                is_graphical;
            unsigned long long  month_tick;
        } currently;

        std::string label;
        
        std::unique_ptr<Population> population;
        std::unique_ptr<Visualizer> canvas;
    };

}
