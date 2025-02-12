#pragma once
#include "response.hh"
#include "data/population.hh"

namespace fargo 
{

    class Publisher
    {
    
    public:
        Publisher(const PopulationData& input_data);
        ~Publisher();

        Response<void> serialize_to_file(const std::string& file_path);

    private:
        const PopulationData& publishee;

    };

}
