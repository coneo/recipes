#include <boost/bind.hpp>
#include <iostream>

class TestClass
{
public:
	void print()
	{
		std::cout << "bind member func" << std::endl;
	}
};

int main(int argc, char* argv[])
{
	TestClass test;
	//boost::bind( &TestClass::print)(); //no class instance , error
	//boost::bind( TestClass::print, &test)(); //need the & to address the func , error
	boost::bind( &TestClass::print, &test)();
	return 0;
}
