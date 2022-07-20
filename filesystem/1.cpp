#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    std::string id;
    std::cout << "please enter route id : " << std::endl;
    std::cin >> id;
    std::string map_name("route_" + id);

    boost::filesystem::path map_path("/opt/holo/hpp/" + map_name);
    if (boost::filesystem::exists(map_path))
    {
        std::cout << "path exist" << std::endl;
        boost::filesystem::path map_path_files("/opt/holo/hpp/" + map_name + "/");
        boost::filesystem::remove_all(map_path_files);

        if (!boost::filesystem::create_directory(map_path))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << map_path << "\n";
            throw std::runtime_error(ss.str());
        }
    }
    else
    {
        std::cout << "path don't exist" << std::endl;
        if (!boost::filesystem::create_directory(map_path))
        {
            std::stringstream ss;
            ss << "MapDatabaseManager --- Failed to create dir: " << map_path << "\n";
            throw std::runtime_error(ss.str());
        }
    }

    // mv $path/frames.bin $path/mappoints.bin $path/pcd.ply $path/vehicle_odometry.txt $path/front_wheel_angle.txt
    // $path/start_point.png $path/map_quality.txt /opt/holo/hpp/route_$1
    // copy_file(source_path, destination_path, copy_option::overwrite_if_exists);
    std::string config_path = "/home/holo/HPP/x86_ubuntu18.04/output/x86_64_ubuntu-18.04/release/target/config/"
                              "holo_localization_parking/vslam";
    // boost::filesystem::copy_file("/home/holo/HPP/x86_ubuntu18.04/output/x86_64_ubuntu-18.04/release/target/config/"
    // "holo_localization_parking/vslam")

    try
    {
        boost::filesystem::copy_file(config_path + "/" + map_name + "/frames.bin",
                                     "/opt/holo/hpp/" + map_name + "/frames.bin");
        boost::filesystem::copy_file(config_path + "/" + map_name + "/mappoints.bin",
                                     "/opt/holo/hpp/" + map_name + "/mappoints.bin");
        boost::filesystem::copy_file(config_path + "/" + map_name + "/pcd.ply",
                                     "/opt/holo/hpp/" + map_name + "/pcd.ply");
        boost::filesystem::copy_file(config_path + "/" + map_name + "/vehicle_odometry.txt",
                                     "/opt/holo/hpp/" + map_name + "/vehicle_odometry.txt");

        boost::filesystem::copy_file(config_path + "/" + map_name + "/front_wheel_angle.txt",
                                     "/opt/holo/hpp/" + map_name + "/front_wheel_angle.txt");
        boost::filesystem::copy_file(config_path + "/start_point.png",
                                     "/opt/holo/hpp/" + map_name + "/start_point.png");
        boost::filesystem::copy_file(config_path + "/" + map_name + "/map_quality.txt",
                                     "/opt/holo/hpp/" + map_name + "/map_quality.txt");
        std::cout << "success copy offline map to /opt" << std::endl;
    }
    catch (boost::filesystem::filesystem_error)
    {
        std::cout << "fail copy offline map to /opt" << std::endl;
    }
}
