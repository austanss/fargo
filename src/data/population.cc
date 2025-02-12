#include "data/population.hh"

using namespace fargo;

StoredPopulation::StoredPopulation() 
{
    this->entities = std::make_unique<EntityCollection>();
}

StoredPopulation::~StoredPopulation() 
{
}

Response<void> StoredPopulation::summarize()
{
    Status current_status = Status::FLAWLESS;

    this->summary.head_count = this->entities->count();

    return Responses::flawless();
}

Population::Population() 
{
    this->data = std::make_unique<StoredPopulation>();
    this->uid_i = 0;
}

Population::~Population() 
{
}

Response<void> Population::reset()
{
    Status latest_status = Status::FLAWLESS;
    
    latest_status = this->reset_population_data().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        return Response<void>(latest_status);
    }

    return Responses::flawless();
}

Response<void> Population::update()
{
    Status latest_status = Status::FLAWLESS;

    latest_status = this->update_durations().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        return Response<void>(latest_status);
    }

    return Responses::flawless();
}

static constexpr unsigned long DEFAULT_START_SIZE = 16;

Response<void> Population::reset_population_data()
{
    Status current_status = Status::FLAWLESS;

    this->data.reset();
    this->data = std::make_unique<StoredPopulation>();

    this->uid_i = 0;

    for (unsigned long i = 0; i < DEFAULT_START_SIZE; i++) {
        this->data->entities->create(this->uid_i++);
    }

    current_status = this->data->summarize().status;
    if (StatusValidator::indicates_intervention(current_status)) {
        return Response<void>(current_status);
    }

    return Responses::flawless();
}

Response<void> Population::update_durations()
{
    Status current_status = Status::FLAWLESS;

    const int count = this->reference_data().entities->count();
    for (int i = 0; i < count; i++)
    {
        this->data->entities->get_by_index(i).month_age++;
    }

    return Responses::flawless();
}

Response<void> Population::update_incomes()
{
    Status current_status = Status::FLAWLESS;

    const int count = this->reference_data().entities->count();
    for (int i = 0; i < count; i++)
    {
        //
    }

    return Responses::flawless();
}

Response<void> Population::update_eligibility()
{
    Status current_status = Status::FLAWLESS;

    const int count = this->reference_data().entities->count();
    for (int i = 0; i < count; i++)
    {
        //
    }

    return Responses::flawless();
}
