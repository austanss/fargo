#include "exec/context.hh"

using namespace fargo;

SimulationContext::SimulationContext() {
    metadata.ssdi_enabled = false;
    metadata.sssi_enabled = false;
    metadata.unem_enabled = false;
    metadata.unemplo_count = 0.0f;
    metadata.wealthy_count = 0;
    metadata.welfare_count = 0;
    metadata.total_count = 0;

    population = {};
    
    chronology.current_day = 0;
}

SimulationContext::~SimulationContext() {
    // Nothing to do here
}
