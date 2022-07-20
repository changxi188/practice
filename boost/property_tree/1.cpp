#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


using namespace std;

int main()
{
    // std::string                 json_file = "./a.json";
    /*
    std::ifstream json_file("./a.json");

    if (!json_file.is_open())
    {
        throw("failed to open json file");
    }

    std::stringstream           ss;

    ss << json_file.rdbuf();
    */

    boost::property_tree::ptree ptree;
    boost::property_tree::read_json("./a.json", ptree);
    std::cout << ptree.get_child("time_stamp").get_child("sec").get_value<int>() << std::endl;

    const auto lane_boundary_node = ptree.get_child("lane_boundaries");

    // for (const auto it = lane_boundary_node.begin(); it != lane_boundary_node.end(); ++it)
    for (const auto it : lane_boundary_node)
    {
        std::cout << it.second.get_child("color").get_value<int>() << std::endl;
        std::cout << it.second.get_child("id").get_value<int>() << std::endl;
        std::cout << "1111 " << std::endl;
    }

    return 0;
}
