#pragma once
#include "response.hh"
#include "data/entity.hh"
#include <memory>

namespace fargo 
{

    // Operated on by Population
    class StoredPopulation
    {

    public:
        StoredPopulation();
        ~StoredPopulation();

        struct {
            unsigned long   head_count;
        } summary;

        Response<void> summarize();

        std::unique_ptr<EntityCollection> entities;
    };

    // Operates on StoredPopulation
    class Population
    {

    public:
        Population(unsigned long size);
        ~Population();

        Response<void> reset();
        Response<void> update();

        const unsigned long root_size;

        inline const StoredPopulation& reference_data() const { return *(this->data); }

    private:
        std::unique_ptr<StoredPopulation> data;

        unsigned long uid_i;

        Response<void> reset_population_data();

        Response<void> update_durations();
        Response<void> update_savings();
        Response<void> update_guess();

    };

}
