#include <unistd.h>
#include <atomic>
#include <iostream>
#include <thread>

using namespace std;
class SpinLockMutex
{
public:
    SpinLockMutex() : flag(ATOMIC_FLAG_INIT)
    {
    }
    void lock()
    {
        while (flag.test_and_set(std::memory_order_acquire))
            ;
    }

    void unlock()
    {
        flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag;
};

int a = 0;

SpinLockMutex spin_lock_mutex;

void th1()
{
    spin_lock_mutex.lock();
    for (int i = 1; i < 5; ++i)
    {
        cin >> a;
        std::cout << "th1 a : " << a << std::endl;
    }
    spin_lock_mutex.unlock();
}

void th2()
{
    sleep(1);
    spin_lock_mutex.lock();
    a++;
    std::cout << "th2 a :  " << a << std::endl;
    spin_lock_mutex.unlock();
}

int main()
{
    std::thread t1(th1);
    std::thread t2(th2);

    t1.join();
    t2.join();

    return 0;
}
