#pragma once
#include <string>
#include <memory>
#include "response.hh"
#include "data/population.hh"
#include "exec/context.hh"

namespace fargo 
{
    class Simulation
    {

    public:
        Simulation(const Context params);
        ~Simulation();

        Response<void> reset();
        Response<void> update();

        inline const std::string& get_label() const { return this->label; }

    private:
        Simulation();

        const Context parameters;

        struct {
            bool                active;
            unsigned long long  month_tick;
        } state;

        std::string label;
        
        std::unique_ptr<Population> population;
    };

}
