#pragma once
#include <string>

namespace fargo {

    class Simulation {

    public:
        // Constructor
        Simulation(const std::string &name);

        // Destructor
        ~Simulation();

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

        // Internal functions
        void display_create();
        void display_destroy();
        void display_update();
    };

}
