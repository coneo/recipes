#include "vartype.h"
#include <iostream>
using namespace std;

void foo(int val)
{
    cout << "foo:" << val << endl;
}

void test_int()
{
    //构造
    VarType var0(98);

    //拷贝构造
    VarType var1(var0);

    //赋值操作符
    VarType var2;
    var2 = var0;

    unsigned long num0 = 3000000000;
    VarType var3(num0);

    //隐式转换
    foo(var1);

    //隐式转换
    int i = var1;

    cout << "var0=" << (int)var0 << endl;
    cout << "var1=" << i << endl;
    cout << "var2=" << (int)var2 << endl;
    cout << "var3=" << (unsigned long)var3 << endl;
}

void test_str()
{
    VarType str0("str0");

    std::string tmpstr1 = "this is std string";
    VarType str1(tmpstr1);

    std::string tmpstr2 = (const char*)str1;
    //这里强转为string实际上是先转为const char*
    cout << "str0=" << (const char*)str0 << endl;
    cout << "str1=" << (std::string)str1 << endl;
    cout << "tmpstr2=" << tmpstr2 << endl;
}

int main(int argc, char**argv)
{
    //test_int();

    test_str();

    return 0;
}
