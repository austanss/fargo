#include "data/population.hh"

using namespace fargo;

Population::Population() {
    this->individuals = new std::vector<std::shared_ptr<Individual>>();
}

Population::~Population() {
    delete this->individuals;
}

std::shared_ptr<Individual> Population::new_individual() {
    std::shared_ptr<Individual> individual = std::make_shared<Individual>();
    this->individuals->push_back(individual);
    return individual;
}

Individual& Population::operator[](const unsigned long index) {
    return *this->individuals->at(index);
}

