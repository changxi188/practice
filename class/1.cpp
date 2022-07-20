#include <iostream>


using namespace std;

class A
{
public:
    A(int a)
    {
        std::cout << "A() " << std::endl;
    }

    virtual ~A()
    {
    }

    int a_;
};

class C
{
public:
    C()
    {
        std::cout << "C() " << std::endl;
    }

    C(const C& c)
    {
        std::cout << "C(const C& c) " << std::endl;
    }
};

class B : public A
{
public:
    B(int aa, const C& c) : c_(c), A(aa)
    {
        std::cout << "B() " << std::endl;
    }

    C c_;
};

int main()
{
    C c;
    B b(11, c);
}
