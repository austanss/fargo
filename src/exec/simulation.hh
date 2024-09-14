#pragma once
#include "exec/context.hh"
#include <string>
#include <memory>

namespace fargo {

    class SimulationHandle {

    public:
        // Constructor
        SimulationHandle(const std::string &name);

        // Destructor
        ~SimulationHandle();

        // Member functions
        void reset(bool should_display);
        void tick();
        bool is_valid();

        std::string moniker;

    private:
        // Member variables
        bool fresh;
        bool displayed;

        void* window;
        unsigned int* buffer;

        std::unique_ptr<SimulationContext> context;

        // Internal functions
        void display_create();
        void display_destroy();
        void display_update();

        void data_update();

    };

}
