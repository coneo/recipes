#include <iostream>
#include <string>

const char* hello() {return __func__;}

int main()
{
		std::cout << hello() << std::endl;
}
