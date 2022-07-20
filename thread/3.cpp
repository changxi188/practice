#include <unistd.h>
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

class A
{
public:
    A()
    {
    }

    void t1()
    {
        std::cout << "hello t1" << std::endl;
        ++count;
    }

    int count = 0;
    ;

    std::shared_ptr<std::thread> A_th1_;
};

int main()
{
    A a;

    std::thread t1(&A::t1, a);
    sleep(1);

    std::cout << "123" << std::endl;

    std::cout << "a.count : " << a.count << std::endl;

    t1.join();
    return 0;
}
