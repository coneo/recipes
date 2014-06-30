#include <iostream>
#include <boost/intrusive_ptr.hpp>

class CCounted;
namespace boost
{
		void intrusive_ptr_add_ref(CCounted *p);
		void intrusive_ptr_release(CCounted *p);
};

class CCounted
{
private:
		long references;
		friend void ::boost::intrusive_ptr_add_ref(CCounted *p);
		friend void ::boost::intrusive_ptr_release(CCounted *p);
public:
		CCounted() : references(0) {}

		long getRefCount() {return references;}
};

namespace boost
{
		inline void intrusive_ptr_add_ref(CCounted *p)
		{
				++(p->references);
		}
		inline void intrusive_ptr_release(CCounted *p)
		{
				if (--(p->references) == 0)
						delete p;
		}
};


int main(int argc, char** argb)
{
		boost::intrusive_ptr<CCounted> count(new CCounted);

		std::cout << "now reference:" << count->getRefCount() << std::endl;
}
