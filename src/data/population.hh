#pragma once
#include "data/individual.hh"
#include <memory>
#include <vector>

namespace fargo {

    class Population {
    
    public:
        // Constructor
        Population();

        // Destructor
        ~Population();

        std::shared_ptr<Individual> new_individual();

        Individual& operator[](const unsigned long index);

        inline unsigned long size() {
            return this->individuals->size();
        }

    private:
        std::vector<std::shared_ptr<Individual>> *individuals;

    };
}
