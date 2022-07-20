#include <iostream>
#include <unordered_map>

using namespace std;


int main()
{
    std::unordered_map<int, string> um1;

    um1.emplace(1, "a");
    um1.emplace(1, "e");
    um1.emplace(2, "b");
    um1.emplace(3, "c");
    um1.emplace(4, "d");

    /*
    for (size_t i = 0; i < um1.size(); ++i)
    {
        std::cout << "um1[i] : " << um1[i] << std::endl;
    }
    std::cout << "um1[i] : " << um1.back().second() << std::endl;
    */

    for (const auto& result : um1)
    {
        std::cout << "result.second :  " << result.second << std::endl;
    }

    std::cout << "count : " << um1.count(1) << std::endl;
    std::cout << "result.second : " << um1[1] << std::endl;

    return 0;
}
