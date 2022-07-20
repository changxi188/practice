#include <unistd.h>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

class B
{
public:
    B()
    {
        B_thread1_ = std::make_shared<std::thread>(std::bind(&B::run, this));
    }

    void run()
    {
        while (true)
        {
            cout << "B run " << endl;
            sleep(1);
        }
    }

private:
    std::shared_ptr<std::thread> B_thread1_;
};

class A
{
public:
    A()
    {
        cout << 11111 << std::endl;
        A_thread1_ = std::make_shared<thread>(std::bind(&A::TestThread1, this, std::placeholders::_1), 1);
        A_thread2_ = std::make_shared<thread>(std::bind(&A::Bus, this));
        // bb_        = std::make_shared<B>();
        cout << 11112 << std::endl;
    }

    void Bus()
    {
        while (true)
        {
            cout << "Bus run push_back data" << endl;
            sleep(1);
        }
    }

    void TestThread1(int i)
    {
        cout << 11111 << std::endl;
        bb_ = std::make_shared<B>();
        while (true)
        {
            cout << "TestThread1()" << endl;
            sleep(1);
        }
        cout << 11111 << std::endl;
    }

    virtual ~A()
    {
        A_thread1_->join();
    }

private:
    std::shared_ptr<std::thread> A_thread1_;
    std::shared_ptr<std::thread> A_thread2_;
    std::shared_ptr<B>           bb_;
};

int main()
{
    A a1;

    return 0;
}
