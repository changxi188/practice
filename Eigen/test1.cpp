#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
#include <sophus/se3.hpp>
#include <sophus/so3.hpp>

using namespace std;

int main(int argc, char** argv)
{
    // 计算 T_cs
    Eigen::Quaterniond R_cs(0.539, -0.842, 0., 0.);
    Eigen::Vector3d    t_cs(0.001172, 2.434104, 0.586145);
    Sophus::SE3d       T_cs(R_cs, t_cs);
    cout << "T_cs : " << endl << T_cs.matrix() << std::endl;

    // 计算 T_bc
    Eigen::Quaterniond R_bc(0.707, 0.0, 0.0, -0.707);
    Eigen::Vector3d    t_bc(1.295, 0, -0.325);
    Sophus::SE3d       T_bc(R_bc, t_bc);
    cout << "T_bc : " << endl << T_bc.matrix() << std::endl;

    // 计算 T_bs
    Sophus::SE3d T_bs = T_bc * T_cs;
    cout << "T_bs : " << endl << T_bs.matrix() << std::endl;

    Eigen::Quaterniond R_bs(T_bs.rotationMatrix().matrix());
    cout << "Q_bs : " << endl << R_bs.normalized().coeffs() << endl;
    cout << "t_bs : " << endl << T_bs.translation() << endl;
    return 0;
}
