#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        std::cout << "A()" << std::endl;
    }

private:
    int a_;
};

class B : public A
{
public:
    B()
    {
        std::cout << "B()" << std::endl;
    }

    void print()
    {
        // std::cout << "a_ : " << a_ << std::endl;
    }
};

int main()
{
    B b;
    // b.a_;
    return 0;
}
