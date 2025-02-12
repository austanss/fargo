#include "exec/context.hh"

using namespace fargo;

Context::Context()
{
    this->restore_defaults();
}

Context::~Context() {}

Response<void> Context::restore_defaults()
{
    this->independents.benefits = false;
    this->independents.restricts = false;
    this->independents.gradually = false;

    this->controls.pop_size = 1000;
    this->controls.monthly_benefit = 1000;
    this->controls.max_months = 12 * 20;

    this->environment.output_path = "fargo.txt";
    this->environment.output_label = "Default";

    return Responses::flawless();
}

static constexpr int SWITCH_DASHES = 1;
static constexpr int VALUE_DASHES = 2;

static constexpr long parameter_count = 8;
static std::string parameter_names[] = {
    "output",           //0
    "label",            //1
    "benefit",          //2
    "restrict",         //3
    "gradual",          //4
    "pop-size",         //5
    "monthly-benefit",  //6
    "max-months"        //7
};

static long index_of_parameter(const std::string& parameter)
{
    for (long i = 0; i < parameter_count; i++) {
        if (parameter == parameter_names[i]) {
            return i;
        }
    }

    return -1;
}

static long count_dashes(const std::string& argument)
{
    long count = 0;
    for (char c : argument) {
        if (c != '-') {
            break;
        }

        count++;
    }

    return count;
}

static Response<std::string> extract_value(const std::string& argument)
{
    long dashes = count_dashes(argument);

    if (dashes != VALUE_DASHES) {
        return Response<std::string>(Status::ERROR_BAD_ARGUMENT, "");
    }

    long start = argument.find_first_of('=');
    if (start == std::string::npos) {
        return Response<std::string>(Status::ERROR_BAD_ARGUMENT, "");
    }
    
    if (++start >= argument.size()) {
        return Response<std::string>(Status::ERROR_BAD_ARGUMENT, "");
    }

    return Response<std::string>(Status::FLAWLESS, argument.substr(start));
}

Response<void> Context::match_parameters_raw(int argc, char** argv) 
{
    for (int i = 1; i < argc; i++) {
        std::string argument = std::string(argv[i]);

        long dashes = count_dashes(argument);

        if (dashes < SWITCH_DASHES || dashes > VALUE_DASHES) {
            return Response<void>(Status::ERROR_BAD_ARGUMENT);
        }

        bool needs_value = (dashes == VALUE_DASHES);

        std::string trimmed = argument.substr(dashes);

        if (!needs_value) {
            switch (index_of_parameter(trimmed)) {
                case 2:
                    this->independents.benefits = true;
                    break;
                case 3:
                    this->independents.restricts = true;
                    break;
                case 4:
                    this->independents.gradually = true;
                    break;
                default:
                    return Response<void>(Status::ERROR_BAD_ARGUMENT);
            }
        }
        else {
            Response<std::string> value = extract_value(argument);
            if (value.status != Status::FLAWLESS) {
                return Response<void>(value.status);
            }

            std::string retrimmed = trimmed.substr(0, trimmed.find_first_of('='));

            switch (index_of_parameter(retrimmed)) {
                case 5:
                    this->controls.pop_size = std::stoul(value.result);
                    break;
                case 6:
                    this->controls.monthly_benefit = std::stoul(value.result);
                    break;
                case 7:
                    this->controls.max_months = std::stoul(value.result);
                    break;
                case 0:
                    this->environment.output_path = value.result;
                    break;
                case 1:
                    this->environment.output_label = value.result;
                    break;
                default:
                    return Response<void>(Status::ERROR_BAD_ARGUMENT);
            }
        }
    }
    return Responses::flawless();
}
