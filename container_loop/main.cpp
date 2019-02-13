#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;
using namespace chrono;

// test size
const int COUNT = 10000000;

class time_count
{
public:
    time_count(string desc_) :
      desc(desc_)
    {
        start = system_clock::now();
    }

    ~time_count()
    {
        auto end = system_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << desc << ":" << double(duration.count()) << " " << "毫秒"<< endl;
    }

private:
    system_clock::time_point start;
    string desc;
};

template<typename T>
void loop(const T& t)
{
    time_count cost("loop");
    for (auto& v : t)
    {
    }
}

struct st
{
    int k;
    int v;
};
int main()
{
    std::vector<st> vec;
    std::list<st> lt;
    std::map<int,int> m1;
    std::unordered_map<int,int> m2;

    time_count cost("create");
    for (int i = 0; i < COUNT; ++i)
    {
        st t;
        t.k = i;
        t.v = i;
        vec.push_back(t);
        lt.push_back(t);
        m1.insert(std::make_pair(i, i));
        m2.insert(std::make_pair(i, i));
    }

    loop(vec);
    loop(lt);
    loop(m1);
    loop(m2);
}
