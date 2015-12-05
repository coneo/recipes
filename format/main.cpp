#include "format.h"
#include <iostream>

using namespace std;

const int times = 10000000;

void test_performance()
{
    for (int i = 0; i < 1000000; ++i)
    {
        string ret;
        format(ret, "{国家}的{玩家}击败了{怪物},获得{物品}{数量}个", "宋国", "hxq666", "野猪", "大保健", 200.223);
    }
}

void test_normal()
{
    string ret="";
    format(ret, "hello {var1},{var2}", "hxq",111);
    cout << ret << endl;
}

int main(int argc, char** argv)
{

#ifdef _PERFORMANCE
    //test_performance();
    for (int i = 0; i < times; ++i)
    {
        string ret;
        format(ret, "{国家}的{玩家}击败了{怪物},获得{物品}{数量}个", "宋国", "hxq666", "野猪", "大保健", 200);
    }
#else
    test_normal();
#endif

    return 0;
}
