#include <iostream>
//#include <Eigen/Dense>
//#include <Eigen/Core>
#include <eigen3/Eigen/Core>
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>
// #include <g2o/core/base_binary_edge.h>
//
//
using namespace std;

int main()
{
    Eigen::Matrix3d    eigen_R;
    Sophus::SE3d       sophus_T;
    Eigen::Quaterniond Q(eigen_R);
    Eigen::Quaterniond Q3(1, 2, 3, 4);
    cout << eigen_R << endl;
    cout << sophus_T.matrix() << endl;
    Q.norm();

    cout << Q.coeffs() << endl;

    Sophus::SO3d       so3_test;
    Eigen::Quaterniond Q2(so3_test.matrix());
    cout << Q2.coeffs() << endl;

    return 0;
}
