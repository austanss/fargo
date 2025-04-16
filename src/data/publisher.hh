#pragma once
#include "response.hh"
#include "data/population.hh"

namespace fargo 
{

    class Publisher
    {
    
    public:
        Publisher(const Population& input_data);
        ~Publisher();

        Response<void> serialize_to_file(const std::string& file_path);

    private:
        const Population& publishee;

    };

}
