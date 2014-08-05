#include "RandomEngine.h"
#include <iostream>

using namespace water;

int main()
{
    RandomEngine<> engine(24);
    //engine.seed(24);
    for (int i = 0; i < 20; ++i)
    {
	std::cout << engine.random() << " ";
	/*
	if (i == 20)
	{
	    engine.seed(24);
	    std::cout << "\n";
	}*/
    }
    std::cout << "\n";

    std::cout <<"default seed=" << std::default_random_engine::default_seed << "\n";
}
