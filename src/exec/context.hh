#pragma once
#include "response.hh"
#include <string>
#include <memory>
#include <vector>


namespace fargo 
{

    class Context
    {

    public:
        Context();
        ~Context();

        Response<void>          restore_defaults();
        Response<void>          match_parameters_raw(int argc, char** argv);

        // Independent variables
        struct {
            bool                benefits;
            bool                restricts;
            bool                gradually;
        } independents;

        // Control variables
        struct {
            unsigned long       pop_size;
            unsigned long       monthly_benefit;
            unsigned long       max_months;
        } controls;

    private:
        

    };

}

