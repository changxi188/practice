#include <iostream>

using namespace std;

enum class Status
{
    PUSE = 0,
    SPIN = 1
};

int main()
{
    Status status = Status::PUSE;

    std::cout << status << std::endl;
    return 0;
}