#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int>  data;
std::atomic<bool> data_ready(false);

void read_thread()
{
    while (!data_ready.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "the answer = " << data[0] << "\n";
}

void writer_thread()
{
    data.emplace_back(1);
    data_ready.store(true);
}

int main()
{
    std::thread t1(read_thread);
    std::thread t2(writer_thread);

    t1.join();
    t2.join();

    return 0;
}

