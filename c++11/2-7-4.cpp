//c++0x not implement ? use c++11 ?

#include <string>

class Member
{
public:
	Member(int i) : m(i){}

private:
	int m;
};

class Group
{
public:
	Group(){} //no need init data,mem,name
	Group(int a):data(a){}	//no need init mem,name
	Group(Member m) : mem(m){}	//no need init data,name
	Group(int a,Member m, std::string s) : data(a),mem(m),name(s){}
private:
	int data = 1;
	Member m{0};
	std::string name{"hello"};
};
