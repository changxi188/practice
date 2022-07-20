#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

int main()
{
    std::cout << "main start" << std::endl;

    std::chrono::duration<int, std::ratio<1, 1000>> d1(3000);
    std::this_thread::sleep_for(d1);
    std::cout << "main over" << std::endl;
    return 0;
}
