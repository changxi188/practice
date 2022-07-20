#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A
{
public:
    A(const int& a) : a_(a)
    {
        std::cout << "A(const int& a) " << std::endl;
    }

    A(const A& a) : a_(a.a_)
    {
        std::cout << "A(const A& a) " << std::endl;
    }

    A(A&& a) : a_(a.a_)
    {
        std::cout << "A(A&& a) " << std::endl;
    }

    ~A()
    {
        std::cout << "~A() " << std::endl;
    }

private:
    int a_;
};

int main()
{
    // std::vector<std::shared_ptr<A>> test;
    std::vector<A> test1;
    test1.reserve(10);

    std::cout << "push back" << std::endl;
    test1.push_back(1);
    test1.emplace_back(1);
    test1.emplace_back(1);
    std::cout << "111111111 " << std::endl;
    test1.emplace_back(1);
    test1.emplace_back(1);

    std::cout << "emplace back" << std::endl;
    std::vector<A> test2;
    test2.reserve(10);
    test2.emplace_back(1);
    std::cout << "222222222 " << std::endl;
    test2.emplace_back(1);
    std::cout << "222222222 " << std::endl;
    test2.emplace_back(1);
    std::cout << "222222222 " << std::endl;
    test2.emplace_back(1);
    std::cout << "222222222 " << std::endl;
    test2.emplace_back(1);

    return 0;
}

