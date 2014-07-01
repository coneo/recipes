#include <boost/smart_ptr.hpp>

int main(int argc, char**argv)
{
		typedef boost::scoped_array<int> int_array;
		typedef boost::scoped_array<int_array> int_array_array;

		int_array_array array(new int_array[10]);

		for (int i = 0; i < 10; ++i)
		{
				array[i].reset(new int[i*10]);
		}

		for (int i = 0; i < 10; ++i)
				for (int j = 0; j < i*10; ++j)
				{
						array[i][j] = i+j;
				}
}
