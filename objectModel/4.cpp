#include <functional>
#include <iostream>

using namespace std;

class B
{
public:
    B()
    {
        std::cout << "B()" << std::endl;
    }

    std::function<void(int)> b_func_;
};

class A
{
public:
    A() : b_()
    {
        std::cout << "A()" << std::endl;

        b_.b_func_ = std::bind(&A::test, this, std::placeholders::_1);
    }

    void test(int i)
    {
        std::cout << "A::test(), i : " << i << std::endl;
    }
    void test2()
    {
        b_.b_func_(1);
    }

private:
    B b_;
};
int main()
{
    A a;
    a.test2();

    return 0;
}
