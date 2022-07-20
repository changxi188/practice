#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>

#include "sophus/se3.hpp"

using namespace std;

// using namespace Eigen;

int main()
{
    /*

    Eigen::Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();

    Quaterniond q(R);

    Sophus::SO3d SO3_R(R);
    Sophus::SO3d SO3_q(q);

    cout << "SO3_R : " << SO3_R.matrix() << endl;
    cout << "SO3_q : " << SO3_q.matrix() << endl;


    Vector3d so3 = SO3_R.log();
    cout << "so3 : " << so3.transpose() << endl;

    cout << "so3 hat : " << Sophus::SO3d::hat(so3) << endl;

    cout << "so3 hat vee " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;


    Vector3d update_so3(1e-4, 0, 0);
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;

    cout << "SO3 update" << SO3_updated.matrix() << endl;


    Vector3d t(0, 0, 1);

    Sophus::SE3d SE3Rt(R, t);
    Sophus::SE3d SE3qt(R, t);

    cout << "SE3Rt : " << SE3Rt.matrix() << endl;
    cout << "SE3qt : " << SE3qt.matrix() << endl;

    typedef Eigen::Matrix<double, 6, 1> Vector6d;

    Vector6d se3 = SE3Rt.log();

    cout << "se3 : " << se3.transpose() << endl;

    cout << "se3 hat" << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 hat vee " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;

    Vector6d se3_update;
    se3_update.setZero();
    se3_update(0, 0) = 1e-4d;

    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(se3_update) * SE3Rt;
    cout << "SE3_updated " << SE3_updated.matrix() << endl;
    */

    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d(0, 0, 1)).toRotationMatrix();

    Eigen::Quaterniond q(R);
    Sophus::SO3d       SO3_R(R);
    Eigen::Vector3d    translation(1, 1, 1);

    Sophus::SE3d SE3_R(SO3_R, translation);
    std::cout << "raw SE3_R : \n" << SE3_R.matrix() << std::endl;
    std::cout << "raw Rotation of SE3 : \n " << SE3_R.rotationMatrix() << std::endl;
    std::cout << "raw translation of SE3 : \n" << SE3_R.translation() << std::endl;
    Eigen::Matrix<double, 6, 1> se3 = SE3_R.log();
    std::cout << "se3 : \n" << se3 << std::endl;
    cout << "se3 hat : \n" << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 update : \n" << Sophus::SE3d::exp(se3).matrix3x4() << endl;
}
