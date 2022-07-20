#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
    A()
    {
        std::cout << "A() start" << std::endl;
    }
    ~A()
    {
        std::cout << "~A() start" << std::endl;
    }
    int a_;
};

int main()
{
    std::shared_ptr<A> p_a = std::make_shared<A>();
    p_a                    = nullptr;

    std::cout << "after nullptr " << std::endl;
    return 0;
}
