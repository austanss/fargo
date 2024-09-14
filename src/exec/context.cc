#include "exec/context.hh"
#include "data/population.hh"

using namespace fargo;

SimulationContext::SimulationContext() {
    metadata.ssdi_enabled = false;
    metadata.sssi_enabled = false;
    metadata.unem_enabled = false;
    metadata.unemplo_count = 0.0f;
    metadata.wealthy_count = 0;
    metadata.welfare_count = 0;
    metadata.total_count = 0;

    this->population = (void *)new Population();

    chronology.current_day = 0;
}

SimulationContext::~SimulationContext() {
    delete (Population *)this->population;
}

void SimulationContext::population_refresh(unsigned long new_size) {
    Population *pop = new Population();
    while (pop->size() < new_size) {
        pop->new_individual();
    }
    delete (Population *)this->population;
    this->population = (void *)pop;
}
