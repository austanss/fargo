#include "publisher.hh"
#include <iostream>
#include <fstream>

using namespace fargo;

Publisher::Publisher(const StoredPopulation& input_data) : publishee(input_data) {}

Publisher::~Publisher() {}

Response<void> Publisher::serialize_to_file(const std::string& file_path)
{
    std::ofstream output;
    output.open(file_path);
    if (!output.is_open())
    {
        return Response<void>(Status::ERROR_FILE_404);
    } 

    output << "Population dataset automatically generated output from Fargo.\n" << std::endl;

    for (unsigned long i = 0; i < publishee.entities->count(); i++) 
    {
        const Entity& entity = publishee.entities->get_by_index(i);
        output << i << ", Indiv." << entity.uid << ",age=" << entity.month_age << " \n";
    }
    
    output << "&" << std::endl;

    output.close();

    return Responses::flawless();
}
