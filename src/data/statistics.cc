#include "data/statistics.hh"
#include <random>
#include <iostream>
#include <fstream>

using namespace fargo;

Distribution::Distribution(const double mu, const double sigma) : median(mu), deviation(sigma) {}

Distribution::Distribution(const Distribution& copy) : median(copy.median), deviation(copy.deviation) {}

NormalRandom::NormalRandom(const Distribution& distr) : dist(distr) 
{
    this->regenerate_seed();
}

NormalRandom::~NormalRandom() {}

void NormalRandom::regenerate_seed() 
{
    std::random_device rdrand {};
    this->prng = std::mt19937 { rdrand() };
}

double NormalRandom::generate(bool unsign) 
{
    std::normal_distribution<double> normal_dist(this->dist.median, this->dist.deviation);
    double value = normal_dist(this->prng);
    if (unsign && value < 0) {
        value = 0;
    }
    return value;
}
    
