#include <boost/bind.hpp>
#include <iostream>

void print()
{
	std::cout << "hello boost" << std::endl;
}

int main(int argc, char *argv[])
{
	//boost::bind(print)(); //correct
	//boost::bind(&print)();  //correct
	boost::bind(&print)();  //correct
	return 0;
}
