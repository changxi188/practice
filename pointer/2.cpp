#include <iostream>

using namespace std;

class A
{
public:
    A(int a) : a_(a)
    {
        std::cout << "A() " << std::endl;
    }

    A& ReturnThis()
    {
        return *this;
    }

    ~A()
    {
        std::cout << "~A() " << std::endl;
    }

    int a_;
};

int main()
{
    A a(1);

    A* b = &a.ReturnThis();

    std::cout << b->a_ << std::endl;

    return 0;
}
