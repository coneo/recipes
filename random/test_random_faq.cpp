#include <random>
#include <iostream>
#include <functional>

int rand_int(int low, int high)
{
    static std::default_random_engine re {};
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(re, Dist::param_type(low, high));
}

/*
double rand_double(double low, double high)
{
    static std::default_random_engine re {};
    using Dist = std::uniform_int_distribution<double>;
    static Dist uid {};
    return uid(re, Dist::param_type(low, high));
}*/

int main()
{
    std::default_random_engine re {};
    re.seed(23);
    std::uniform_int_distribution<int> one_to_six {1,6};

    //bind
    auto dice = std::bind(one_to_six, re);
    for (int i = 0; i < 20; ++i)
	std::cout << dice() << " ";
    std::cout << std::endl;

    for (int i = 0; i < 20; ++i)
	std::cout << rand_int(1,7) << " ";
    std::cout << std::endl;
}
