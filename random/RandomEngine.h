#ifndef WATER_BASE_RANDOM_ENGINE_HPP
#define WATER_BASE_RANDOM_ENGINE_HPP

#include <random>

namespace water {

template<typename Engine = std::default_random_engine>
class RandomEngine
{
public:
    typedef typename Engine::result_type result_type;

    RandomEngine(result_type seed = Engine::default_seed) : 
	m_engine(seed)
    {
    }
    ~RandomEngine() = default;

    void seed(result_type value){ m_engine.seed(value); }

    unsigned int random() { return m_dist(m_engine); }

    void discard(unsigned long long step) { m_engine.discard(step); }

private:
    Engine m_engine;
    std::uniform_int_distribution<int> m_dist; //FIXME: use template
};

}
#endif //#define WATER_BASE_RANDOM_ENGINE_HPP
