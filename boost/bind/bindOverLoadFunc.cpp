#include <boost/bind.hpp>
#include <iostream>

struct Func
{
	int& get()	//���غ���1
	{
		std::cout << "overload one" << std::endl;
	}
	int const& get() const//���غ���2
	{
		std::cout << "overload two" << std::endl;
	}
};
int main(int argc, char *argv[])
{
	Func func;

	//boost::bind(&Func::get, &func);   //error
	//boost::bind(static_cast< int const& (Func::*) () const > (&Func::get), _1); //ת��Ϊָ�������غ���������

	typedef int& (Func::*OverloadFuncType) ();
	boost::bind(static_cast<OverloadFuncType>(&Func::get), &func)();
	boost::bind(static_cast<OverloadFuncType>(&Func::get), &func)();
	return 0;
}
