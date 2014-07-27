#include <iostream>
#include <stdexcept>
using namespace std;

void Printf(const char* s)
{
    while(*s)
    {
        if (*s == '%' && *++s != '%')
            throw runtime_error("missing arg");
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void Printf(const char* s, T value, Args... args)
{
    while(*s)
    {
        if (*s == '%' && *++s != '%')
        {
            cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
    throw runtime_error("extra arg privoted to printf");
}

int main()
{
    Printf("int=%d,str=%s\n", 23,"hello");
}
