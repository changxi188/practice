#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> vvv;
    for (const auto v : vvv)
    {
        std::cout << "vector : " << v << std::endl;
    }

    // vvv.resize(2);
    vvv.reserve(10);

    std::cout << vvv.at(1) << std::endl;

    return 0;
}
