#include <boost/circular_buffer.hpp>
#include <iostream>

void printout(boost::circular_buffer<int> &buffer)
{
	unsigned int size = buffer.size();
	for (unsigned int i = 0; i < size; ++i)
		std::cout << buffer[i] << "\t";
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	boost::circular_buffer<int> buffer(3);
	buffer.push_back(1);
	buffer.push_back(2);
	buffer.push_back(3);
	printout(buffer);

	buffer.push_back(4);
	buffer.push_back(5);
	printout(buffer);

	return 0;
}
