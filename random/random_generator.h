#ifndef WATER_BASE_RANDOM_GENERATOR_HPP
#define WATER_BASE_RANDOM_GENERATOR_HPP

#include <random>

namespace water {

template<typename T = uint32_t,
    	 typename Engine = std::default_random_engine,
	 typename Dist = std::uniform_int_distribution<T> >
class RandomGenerator
{
public:
    typedef typename Engine::result_type result_type;
    typedef typename Dist::param_type param_type;

    RandomGenerator(result_type seed = Engine::default_seed) : 
	m_engine(seed)
    {
    }
    ~RandomGenerator() = default;

    Engine& engine() { return m_engine; }

    Dist& distribution() { return m_dist; }

    void seed(result_type value){ m_engine.seed(value); }

    void param(result_type p1, result_type p2){ m_dist.param(param_type(p1,p2)); }

    result_type random() { return m_dist(m_engine); }

    void discard(unsigned long long step) { m_engine.discard(step); }

private:
    Engine m_engine;
    Dist m_dist;
    //result_type m_seed {Engine::default_seed}; //FIXME: remove it
};

/*
template<typename T = uint32_t,
    	 typename Engine = std::default_random_engine,
	 typename Dist = std::uniform_int_distribution<T> >
SerializeStream<buffer::RawBuffer>& operator << (SerializeStream<buffer::RawBuffer>& ss, const RandomGenerator<T,Engine,Dist>& engine)
{
    std::stringstream output;
    output << engine.engine();
    ss << output;
    return ss;
}
template<typename T = uint32_t,
    	 typename Engine = std::default_random_engine,
	 typename Dist = std::uniform_int_distribution<T> >
SerializeStream<buffer::RawBuffer>& operator >> (SerializeStream<buffer::RawBuffer>& ss, const RandomGenerator<T,Engine,Dist>& engine)
{
    std::stringstream input;
    ss >> input;
    input >> engine.engine();
    return ss;
}*/

}
#endif //#define WATER_BASE_RANDOM_GENERATOR_HPP
