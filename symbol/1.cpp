#include <iostream>

using namespace std;

typedef int Key;

class Symbol
{
public:
    Symbol(char c, int j) : c_(c), j_(j)
    {
    }

private:
    char c_;
    int  j_;
};

Key A(int j)
{
    return (Key)Symbol('a', j);
}

Key B(int j)
{
    return (Ke)Symbol('b', j);
}

int main()
{
    std::cout << A(1) << std::endl;
}

