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

void printMinMax()
{
    std::default_random_engine re {};
    std::uniform_int_distribution<int> one_to_six {1,6};
    std::cout << "engine.min=" << re.min() <<"\n";
    std::cout << "engine.max=" << re.max() <<"\n";
    std::cout << "dist.min=" << one_to_six.min() <<"\n";
    std::cout << "dist.max=" << one_to_six.max() <<"\n";
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
    std::uniform_int_distribution<int> dist;

    //bind
    /*
    auto dice = std::bind(one_to_six, re);
    for (int i = 0; i < 20; ++i)
	std::cout << dice() << " ";
    std::cout << std::endl;
    */

    re.seed(20);
    for (int i = 0; i < 10; ++i)
    {
	std::cout << dist(re) << " ";
	if (i == 4) re.discard(10);
    }
    std::cout << std::endl;
    re.seed(20);
    for (int i = 0; i < 20; ++i)
    {
	std::cout << dist(re) << " ";
    }
    std::cout << std::endl;
}
