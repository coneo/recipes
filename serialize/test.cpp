#include "Archive.h"

class Object{
public:
	int a;
	int b;
	int c;
};
class Object1{
public:
	Object b;
	std::vector<Object> os;
	std::vector<int> is;
	std::map<int,int> ms;
};
IMP_SERIALIZE_OBJECT(Object)
{
	BIND(a,1);
	BIND(b,2);
	BIND(c,3);
}
IMP_SERIALIZE_OBJECT(Object1)
{
	BIND(b,1);
	BIND(os,5);
	BIND(is,6);
	BIND(ms,3);
}
int main(int argc, char**argv)
{
	BYTE_ARRAY *out;
	Object1 o1;
	Stream ss(o1,&out);

	Object1 o2;
	Stream ss2(o2,out);
	delete out;
	return 0;
}
