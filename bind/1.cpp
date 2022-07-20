#include <functional>
#include <iostream>

int raw_fun(int a, int b)
{
    return a + b;
}

int main()
{
    auto fun1 = std::bind(raw_fun, std::placeholders::_1, std::placeholders::_2);
    auto fun2 = std::bind(raw_fun, std::placeholders::_1, 1);

    std::function<int(int, int)> f1 = std::bind(raw_fun, std::placeholders::_1, std::placeholders::_2);
    std::cout << fun1(1, 2) << std::endl;
    std::cout << fun2(1) << std::endl;
    std::cout << f1(1, 2) << std::endl;
    return 0;
}