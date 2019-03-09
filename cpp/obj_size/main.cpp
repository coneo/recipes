#include <iostream>

// 指针在我的机器下面是8字节
// 对于继承的情况，只要没有用到多态，对象的内存布局还是很清晰的
// 内存对齐会撑一些内存，而且不同机器可能不一样，用pack可以做到符合预期
#pragma pack(1)
class base
{
    int p1;
    char p2;
};

class d : public base
{
    int p1;
    char aa;
};

int main()
{
    int a;
    std::cout << "base:" << sizeof(base) << std::endl;
    std::cout << "d:" << sizeof(d) << std::endl;
    std::cout << "a:" << sizeof(&a) << std::endl;
}
