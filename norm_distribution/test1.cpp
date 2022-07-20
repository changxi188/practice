#include <iostream>

using namespace std;

namespace test1
{
class A
{
public:
    int i = 0;

private:
};
class B
{
public:
    static A   m_sa;
    static int i;

private:
    static int j;
};
A B::m_sa;
}  // namespace test1

int main()
{
    test1::A a1;
    test1::B b1;
    // test1::B::j;
    test1::B::i;
    cout << b1.m_sa.i << endl;

    return 0;
}
