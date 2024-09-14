#pragma once
#include <string>

namespace fargo {

    class SimulationContext {

    public:
        // Constructor
        SimulationContext();

        // Destructor
        ~SimulationContext();

        struct {
            bool            ssdi_enabled;
            bool            sssi_enabled;
            bool            unem_enabled;
            float           unemplo_count;
            unsigned long   wealthy_count;
            unsigned long   welfare_count;
            unsigned long   total_count;
        } metadata;

        struct {
            unsigned long   current_day;
        } chronology;

        void *population;

        void population_refresh(unsigned long new_size);
    };

}
