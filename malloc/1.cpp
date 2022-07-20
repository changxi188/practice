#include <malloc.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    // std::unordered_map<std::string, std::string>* map = new std::unordered_map<std::string, std::string>();
    std::vector<std::string>                                  vector_string;

    std::unordered_map<std::string, std::vector<std::string>> map;
    for (size_t i = 0; i < 10000; ++i)
    {
        vector_string.push_back(to_string(i));
        map.emplace(to_string(i), vector_string);
    }

    sleep(10);

    map.clear();
    std::cout << "cleard " << std::endl;
    sleep(5);

    for (size_t i = 0; i < 20000; ++i)
    {
        std::cout << "********** vector cap : " << vector_string.capacity() << std::endl;
        std::cout << "********** vector size : " << vector_string.size() << std::endl;
        vector_string.push_back(to_string(i));
        map.emplace(to_string(i), vector_string);
    }

    sleep(5);

    // map.~unordered_map();
    map = std::unordered_map<std::string, std::vector<std::string>>();

    /*
    std::unordered_map<std::string, std::string>().swap(map);
    malloc_trim(0);
    */


    while (true)
    {
        std::cout << "thread is running " << std::endl;
        sleep(1);
    }
    return 0;
}
