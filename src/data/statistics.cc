#include "data/statistics.hh"
#include <random>
#include <iostream>
#include <fstream>

using namespace fargo;

Distribution::Distribution(const double mu, const double sigma) : median(mu), deviation(sigma) {}

Distribution::Distribution(const Distribution& copy) : median(copy.median), deviation(copy.deviation) {}

NormalRandom::NormalRandom(const Distribution& dist) : distribution(dist) 
{
    this->regenerate_seed();
}

NormalRandom::~NormalRandom() {}

void NormalRandom::regenerate_seed() 
{
    std::random_device rdrand {};
    this->prng = std::mt19937 { rdrand() };
}

double NormalRandom::generate() 
{
    std::normal_distribution<double> normal_dist(this->distribution.median, this->distribution.deviation);
    return normal_dist(this->prng);
}
