#include <iostream>
#include <unordered_map>

int main()
{
    std::unordered_map<int, int> a;
    a[0] = 2;

    std::cout << "a[0] : " << a[0] << std::endl;
    std::cout << "a[1] : " << a[1] << std::endl;
    std::cout << "a[2] : " << a[2] << std::endl;
}
