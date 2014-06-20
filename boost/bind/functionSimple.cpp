#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

namespace
{
	void print(int param1, float param2, std::string param3)
	{
		std::cout << "\nint:" << param1 << "\nfloat:" << param2 << "\nstring:" << param3 <<std::endl;
	}
}
int main(int argc,char** argv)
{
	//delecare function var
	boost::function<void(void)> voidFunction; 
	boost::function<void(float)> floatFunction;
	boost::function<void(int,float,std::string)> allFunction;

	//bind methods
	voidFunction	= boost::bind(::print,3, 4.5, "hello voidFunction");
	floatFunction	= boost::bind(::print,4, _1, "hello floatFunction");
	allFunction	= boost::bind(::print,_1, _2, _3);

	//call methods
	voidFunction();
	floatFunction(3.4);
	allFunction(4, 5.6, "hello allFunction");
}
