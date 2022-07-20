#include <eigen3/Eigen/Core>
#include <iostream>

using namespace std;

int main()
{
    Eigen::Vector3d p0, p1;
    std::cout << "please enter p0, p1 " << std::endl;

    std::cout << "please enter p0: " << std::endl;
    std::cin >> p0[0] >> p0[1] >> p0[2];

    std::cout << "please enter p1: " << std::endl;
    std::cin >> p1[0] >> p1[1] >> p1[2];

    // compute distance between two point
    std::cout << "distance : " << (p0 - p1).norm() << std::endl;

    return 0;
}

