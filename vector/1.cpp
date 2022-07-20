#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> a{4, 5, 6, 1, 2, 3};

    for (const auto aa : a)
    {
        std::cout << "aa : " << aa << std::endl;
    }

    std::cout << " *************************************  " << std::endl;

    a.resize(4);
    for (const auto aa : a)
    {
        std::cout << "aa : " << aa << std::endl;
    }

    std::cout << " *************************************  " << std::endl;
    std::swap(a.front(), a.back());

    for (const auto aa : a)
    {
        std::cout << "aa : " << aa << std::endl;
    }
    std::cout << "  **************************************************************************  " << std::endl;

    std::vector<int> b{6, 3, 1, 2, 4, 5, 7, 1, 2, 3};
    for (const auto bb : b)
    {
        std::cout << " bb : " << bb << std::endl;
    }

    for (size_t i = 0; i < b.size();)
    {
        if (b.at(i) < 3)
        {
            std::swap(b.at(i), b.back());
            b.pop_back();
        }
        else
        {
            i++;
        }
    }
    std::cout << "  **************************************************************************  " << std::endl;

    for (const auto bb : b)
    {
        std::cout << " bb : " << bb << std::endl;
    }

    return 0;
}
