#pragma once

namespace fargo {

    class SimulationWorker {

    public:
        // Constructor
        SimulationWorker();

        // Destructor
        ~SimulationWorker();

        void process_individual(void* individual);
    };

}
