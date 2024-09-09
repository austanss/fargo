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

        } population;

        struct {
            unsigned long   current_day;
        } chronology;

    };

}