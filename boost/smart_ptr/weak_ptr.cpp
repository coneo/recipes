#include <boost/smart_ptr.hpp>

struct A;
struct B;

struct A
{
public:
		//boost::shared_ptr<B> ptrToB;
		boost::weak_ptr<B> ptrToB;

		void doSomething()
		{
				boost::shared_ptr<B> strongB = ptrToB.lock(); //weak_ptr to shared_ptr
				if (strongB) //check if alive
						;
		}
};
struct B
{
public:
		boost::shared_ptr<A> ptrToA;
		
		void doSomething(){}
};

int main(int argc, char**argv)
{
		boost::shared_ptr<A> my_a(new A);
		boost::shared_ptr<B> my_b(new B);

		my_a->ptrToB = my_b;
		my_b->ptrToA = my_a;
}
