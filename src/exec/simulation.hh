#pragma once
#include <string>
#include <memory>
#include "response.hh"
#include "data/population.hh"

namespace fargo 
{
    class Simulation
    {

    public:
        Simulation(const std::string& new_label);
        ~Simulation();

        Response<void> reset();
        Response<void> update();

        inline const std::string& get_label() const { return this->label; }

    private:
        Simulation();

        struct {
            bool                is_running;
            unsigned long long  month_tick;
        } currently;

        std::string label;
        
        std::unique_ptr<Population> population;
    };

}
