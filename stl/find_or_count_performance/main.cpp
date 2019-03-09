#include "../../performance_kit.h"
#include <map>

int main()
{
    std::map<int,int> a;

    for (int i = 0; i < 1000000; ++i)
    {
        a.insert(std::make_pair(i,i));
    }

    {
        int b = 0;
        auto f1 = [&]()
        {
            auto it = a.find(555);
            if (it != a.end()){
                b = it->second;
            }
        };

        auto f2 = [&]()
        {
            if (a.count(555)) {
                b = a[555];
            }
        };

        CALL_TIMES_AND_TIME(1000000, "11", f1()) // 126 毫秒
        CALL_TIMES_AND_TIME(1000000, "22", f2()) // 225 毫秒

        // if (a.find(555) != a.end()) // 131 毫秒
        // if (a.count(555)) // 99 毫秒
        // count的方式居然效率比find的方式快,是因为比较么
    }
}
