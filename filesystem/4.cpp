#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    std::vector<std::string> file_names;
    file_names.reserve(3000);
    std::ifstream file_list(
        "/home/holo/sata/luowa_underground_parkinglot/1970-01-01-08-13-55/lane_detection/file_list");

    if (!file_list.is_open())
    {
        throw("failed to open file");
    }

    std::string file_name;
    while (file_list.good())
    {
        file_list >> file_name;
        if (file_list.fail())
        {
            break;
        }

        file_names.emplace_back(file_name.erase(3, 1));
    }

    file_list.close();

    for (const auto file_name : file_names)
    {
        std::cout << "file_name : " << file_name << std::endl;
    }
    std::cout << "file_names size : " << file_names.size() << std::endl;

    char        a[2] = "0";
    std::vector<std::string> aaa;
    aaa.push_back(a);
    std::cout << "aaa : " << aaa[0] << std::endl;

    return 0;
}

