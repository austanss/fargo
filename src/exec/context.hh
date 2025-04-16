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
        Context(const Context& copy);

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
            unsigned long       asset_cutoff;
            unsigned long       max_months;
        } controls;

        struct {
            std::string         output_path;
            std::string         output_label;
        } environment;

    private:
        

    };

}

