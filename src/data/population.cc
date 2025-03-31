#include "data/population.hh"
#include "data/statistics.hh"

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

Population::Population(unsigned long size) : root_size(size)
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

    latest_status = this->update_savings().status;
    if (StatusValidator::indicates_intervention(latest_status)) {
        return Response<void>(latest_status);
    }

    return Responses::flawless();
}

Response<void> Population::reset_population_data()
{
    Status current_status = Status::FLAWLESS;

    this->data.reset();
    this->data = std::make_unique<StoredPopulation>();

    this->uid_i = 0;

    const Distribution age_distro = Distribution(50.0, 15.0);
    for (unsigned long i = 0; i < root_size; i++) {
        NormalRandom new_ages = NormalRandom(age_distro);
        this->data->entities->create(this->uid_i++);
        this->data->entities->get_by_index(i).month_age = (12 * new_ages.generate(true));
    }

    const Distribution income_distro = Distribution(5295.0, 6795.0); // pincs
    for (unsigned long i = 0; i < root_size; i++) {
        NormalRandom new_incomes = NormalRandom(income_distro);
        Entity& entity = this->data->entities->get_by_index(i);
        entity.month_revenue = new_incomes.generate(true);
    }

    // EXPENSES are extremely extremely extremely difficult to even begin to attempt to model
    const Distribution expense_distro = Distribution(5200.0, 6700.0);
    for (unsigned long i = 0; i < root_size; i++) {
        Entity& entity = this->data->entities->get_by_index(i);

        double fiscal_proportion = entity.month_revenue / income_distro.median;

        NormalRandom new_expenses = NormalRandom( {
             expense_distro.median * fiscal_proportion, 
             expense_distro.deviation * fiscal_proportion 
        });

        entity.month_expense = new_expenses.generate(true);
        while (entity.month_revenue < entity.month_expense) {
            entity.month_expense = new_expenses.generate(true);
        }
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

Response<void> Population::update_savings()
{
    Status current_status = Status::FLAWLESS;

    const int count = this->reference_data().entities->count();
    for (int i = 0; i < count; i++)
    {
        Entity& entity = this->data->entities->get_by_index(i);
        entity.total_savings += (entity.month_revenue - entity.month_expense);
    }

    return Responses::flawless();
}
