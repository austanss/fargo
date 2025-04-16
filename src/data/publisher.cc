#include "data/publisher.hh"
#include "exec/bureaucracy.hh"
#include <iostream>
#include <fstream>

using namespace fargo;

Publisher::Publisher(const Population& input_data) : publishee(input_data) {}

Publisher::~Publisher() {}

Response<void> Publisher::serialize_to_file(const std::string& file_path)
{
    Bureaucrat bureau = Bureaucrat();
    bureau.contextualize(this->publishee.context);

    std::ofstream output;
    output.open(file_path);
    if (!output.is_open())
    {
        return Response<void>(Status::ERROR_FILE_404);
    } 

    output << "Index,Age in months,Total balance,Revenue monthly,Expenses monthly" << std::endl;

    for (unsigned long i = 0; i < publishee.reference_data().entities->count(); i++) 
    {
        const Entity& entity = publishee.reference_data().entities->get_by_index(i);
        output << entity.uid << ",";
        output << entity.month_age << ",";
        output << entity.total_balance << ",";
        output << (entity.month_revenue + bureau.see_benefit(entity)) << ","; 
        output << entity.month_expense << "\n";
    }
    
    output << "\n\n" << std::endl;

    output.close();

    return Responses::flawless();
}
