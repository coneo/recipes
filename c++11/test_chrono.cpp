#include <iostream>
#include <chrono>
#include <ctime>

long fibonacci(int n)
{
    if (n < 3) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << std::endl;

    std::chrono::duration<double> elapsed_sec = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finish comutation at " << std::ctime(&end_time)
	      << "elapsed time: " << elapsed_sec.count() << std::endl;
}
