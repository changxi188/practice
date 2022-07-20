#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include <boost/circular_buffer.hpp>

using namespace std;

std::mutex                  buffer_mutex;
std::condition_variable     cv;
boost::circular_buffer<int> buffer(5);

void Th1()
{
    // for (int i = 0; i < 6; ++i)
    int i = 0;
    while (true)
    {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        buffer.push_back(++i);
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " push : " << i << std::endl;
    }
}

void Th2()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(buffer_mutex);
        cv.wait(lock, [] { return !buffer.empty(); });
        std::cout << buffer.front() << std::endl;
        buffer.pop_front();
    }
}

int main()
{
    std::thread t1(Th1);
    std::thread t2(Th2);

    t1.join();
    t2.join();
    return 0;
}

