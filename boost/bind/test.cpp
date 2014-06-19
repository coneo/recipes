#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

void add(int i, int j)
{
	std::cout << i + j << std::endl;
}

void print()
{
	std::cout << "hello print" << std::endl;
}

int main(int argc, char *argv[])
{
	/*
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	//std::for_each(vec.begin(), vec.end(), boost::bind(add, 10, _1));
	std::for_each(vec.begin(), vec.end(), boost::bind(print));
	*/
	boost::bind(print)();
	return 0;
}
