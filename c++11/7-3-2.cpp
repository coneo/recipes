int main()
{
    []{};
    int a = 2;
    int b = 4;
    [=] {return a+b; }; //按值传递
    auto fun1 = [&](int c) {return b = a + c;}; //按引用传递
    auto fun2 = [=, &b](int c) ->int { return b += a + c;}; //按引用传递b，其他参数按引用传递,完整表达式
}
