#pragma once
#include "response.hh"
#include "data/entity.hh"
#include <memory>

namespace fargo 
{

    // Operated on by Population
    class PopulationData
    {

    public:
        PopulationData();
        ~PopulationData();

        struct {
            unsigned long   head_count;
        } summary;

        Response<void> summarize();

        std::unique_ptr<EntityCollection> entities;
    };

    // Operates on PopulationData
    class Population
    {

    public:
        Population();
        ~Population();

        Response<void> reset();
        Response<void> update();

        inline const PopulationData& reference_data() const { return *(this->data); }

    private:
        std::unique_ptr<PopulationData> data;

        unsigned long uid_i;

        Response<void> reset_population_data();

        Response<void> update_advance_ages();
        Response<void> update_handle_births();
        Response<void> update_handle_deaths();

    };

}
