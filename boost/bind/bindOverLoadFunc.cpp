#include <boost/bind.hpp>
#include <iostream>

/*
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
}*/

namespace 
{
	void overload(int param1,float param2,int param3){}
	void overload(float param){}
	void overload(int param){}

	class Class
	{
	public:
		void overload(float param){}
		void overload(int param){}
	};
}

int main(int argc, char** argv)
{
	boost::bind(::overload,_1,_2,_3);
	typedef void (*NoMemFuncType)(int);
	boost::bind(static_cast<NoMemFuncType>(::overload),_1);

	Class instance;
	typedef void (Class::*OverloadFuncType)(float);
	boost::bind(static_cast<OverloadFuncType>(&Class::overload), &instance,_1);
}
