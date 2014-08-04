#include <random>
#include <iostream>

void roll_a_fair_die()
{
    //std::random_device rdev{}; //change seed by time
    std::default_random_engine e{22};
    e.seed(13445);
    std::uniform_int_distribution<int> d{5,80};
    for (int i = 0; i < 20; ++i)
	std::cout << d(e) <<" " ;
    std::cout << e;
    std::cout << std::endl;
}

bool testEngineEqual(const std::default_random_engine &e1,
		     const std::default_random_engine &e2)
{
    return (e1 == e2);
}

int main()
{
    roll_a_fair_die();
}
