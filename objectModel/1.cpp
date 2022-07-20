#pragma pack(1)
#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
    A()
    {
    }
    int a;
    static int b;
};

class B
{
public:
    B(const A& _a) : a(_a)
    {
        // bb_.reserve(100);
        bb_.reserve(100);
    }
    int i;
    A a;

    struct Paragma
    {
        int p1;
        // int p2;
    };
    Paragma Param;
    std::vector<int> bb_;
};

/*
int main()
{
    A a;
    B b(a);
    std::cout << sizeof(b) << std::endl;
    for (int i = 0; i < 1000; ++i)
    {
        b.bb_.push_back(i);
    }
    std::cout << sizeof(b) << std::endl;
    std::cout << &b << std::endl;
    std::cout << &b.i << std::endl;
    std::cout << &b.a << std::endl;
    std::cout << &b.Param << std::endl;
    std::cout << &b.bb_ << std::endl;
    return 0;
}
*/
int main()
{
    A a;
    std::cout << "sizeof(a) : " << sizeof(a) << std::endl;
}
