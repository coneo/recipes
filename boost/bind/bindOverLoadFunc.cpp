#include <boost/bind.hpp>
#include <iostream>

struct Func
{
	int& get()	//重载函数1
	{
		std::cout << "overload one" << std::endl;
	}
	int const& get() const//重载函数2
	{
		std::cout << "overload two" << std::endl;
	}
};
int main(int argc, char *argv[])
{
	Func func;

	//boost::bind(&Func::get, &func);   //error
	//boost::bind(static_cast< int const& (Func::*) () const > (&Func::get), _1); //转换为指定的重载函数，可行

	typedef int& (Func::*OverloadFuncType) ();
	boost::bind(static_cast<OverloadFuncType>(&Func::get), &func)();
	boost::bind(static_cast<OverloadFuncType>(&Func::get), &func)();
	return 0;
}
