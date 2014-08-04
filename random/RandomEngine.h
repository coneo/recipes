#ifndef WATER_BASE_RANDOM_ENGINE_HPP
#define WATER_BASE_RANDOM_ENGINE_HPP

#include <random>

namespace water {
class RandomEngine
{
pulbic:
    RandomEngine() = default;
    ~RandomEngine() = default;

    void seed(int value){ m_engine.seed(value); }

private:
    std::default_random_engine m_engine;
    std::uniform_int_distribution m_dist;
};

}
#endif //#define WATER_BASE_RANDOM_ENGINE_HPP
