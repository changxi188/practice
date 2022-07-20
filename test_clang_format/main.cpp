#include <Eigen/Core>
#include <iostream>
#include <string>

using namespace std;
class A
{
public:
    A()
    {
    }
    ~A()
    {
    }

private:
    int aaa;
};

class B
{
public:
};

class C
{
public:
    int a;
    int b;
    int f;
    C()
    {
    }
    ~C()
    {
    }

    void test(int a, int b);

private:
    int c;

private:
    int d;

public:
    int e;
};

class D
{
public:
    D()
    {
    }
    ~D()
    {
    }

private:
    int a;
    int b;
    int c;
};
void C::test(int a, int b)
{
    if (a == b)
    {
        cout << a << endl;
    }
}

void test_kuohao()
{
    cout << "wrong " << endl;
}

void aaa()
{
    int a = 1;
    int b = 2;
    cout << a + b << endl;
}

int main()
{
    std::cout << "aaa" << std::endl;
    aaa();
    return 0;
}
