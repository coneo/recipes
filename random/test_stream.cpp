#include <random>
#include <sstream>
#include <iostream>

using namespace std;

int main()
{
    typedef std::default_random_engine Engine;
    Engine e(21);
    std::stringstream ss;
    ss << e;
    cout << "random:" << e() << endl;

    Engine e2;
    ss >> e2;
    cout << "random:" << e2() << endl;
}
