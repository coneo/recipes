#include <boost/bind.hpp>
#include <iostream>

template<typename T>
void add(T arg1, T arg2)
{
	std::cout << arg1 + arg2 << std::endl;
}

int main(int argc, char *argv[])
{
	//boost::bind(add<int>,_1,_2)(3,4);
	boost::bind(&add<int>,_1,_2)(3,4);
	return 0;
}

