#pragma once
#include <string>
#include <memory>
#include "exec/response.hh"
#include "gfx/visualizer.hh"

namespace fargo 
{
    class Simulation
    {

    public:
        Simulation(const bool enable_graphic, const std::string& new_label);
        ~Simulation();

        Response<void> reset();
        Response<void> update();

        inline const std::string& get_label() const { return this->label; }

    private:
        Simulation();

        bool is_graphical;
        std::string label;
        
        std::unique_ptr<Visualizer> canvas;
    };

}
