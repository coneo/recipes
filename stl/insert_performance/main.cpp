#include <vector>
#include <list>
#include <string>

struct st
{
    int a = 0;
    int b = 0;
    std::string c = "";
};

int main()
{
    const int times = 10000000;

    std::vector<st> v;
    std::list<st> l;

    for (int i = 0; i < times; ++i)
    {
        st t;
        t.a = i;
        t.b = i + 22;
        t.c = "heheh";
        v.push_back(t);
        //l.push_back(t);
    }
    return 0;
}
