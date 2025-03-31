#pragma once
#include <random>

namespace fargo
{

    class Distribution
    {

    public:
        Distribution(const double mu, const double sigma);
        Distribution(const Distribution& copy);
        double median;
        double deviation;

    };

    class NormalRandom
    {
    
    public:
        NormalRandom(const Distribution& dist);
        ~NormalRandom();
        void regenerate_seed();
        // unsign: returns zero if negative
        double generate(bool unsign);

    private:
        Distribution dist;
        std::mt19937 prng;
    };

}
