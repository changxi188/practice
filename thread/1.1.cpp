#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

std::shared_ptr<std::thread> p_t1;

class B
{
public:
    B()
    {
        std::cout << std::this_thread::get_id() << " : B() " << std::endl;
    }

    ~B()
    {
        std::cout << std::this_thread::get_id() << " : ~B()" << std::endl;
    }

private:
    int b_;
};

class A
{
public:
    A()
    {
        std::cout << std::this_thread::get_id() << " : A() " << std::endl;
        p_ta_ = std::make_shared<std::thread>(std::bind(&A::TestA, this));
        p_b_  = std::make_shared<B>();
    }
    ~A()
    {
        p_ta_->join();
        std::cout << std::this_thread::get_id() << " : ~A()" << std::endl;
    }

    void TestA()
    {
        for (int i = 0; i < 3; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "TestA() running" << std::endl;
        }
        p_b_ = nullptr;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "TestA() over" << std::endl;
    }

private:
    int a_;
    std::shared_ptr<B>           p_b_;
    std::shared_ptr<std::thread> p_ta_;
};

int main()
{
    A a;

    std::this_thread::sleep_for(std::chrono::seconds(6));
    std::cout << "main() end" << std::endl;

    return 0;

}
