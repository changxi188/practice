#include "common_include.h"
#include "curve_fitting_GN.h"
#include "curve_fitting_g2o.h"
#include "problem.h"
#include <Eigen/Cholesky>
#include <vector>

std::vector<int> a;
using namespace std;


int main() {
    /*
    CurveFittingGN::Ptr curve_fitting_GN = std::make_shared<CurveFittingGN>();
    curve_fitting_GN->gaussNewton();

    CurverFitting_G2O::Ptr curve_fitting_g2o = std::make_shared<CurverFitting_G2O>();
    curve_fitting_g2o->startOptimize();

    Eigen::Matrix2d down;
    down << 1, 0, 2, 1;
    Eigen::Matrix2d P = down * down.transpose();
    P.llt();
     */
    Eigen::Quaterniond q1 = Eigen::Quaterniond(1, 1., 2., 3.);
    Eigen::Quaterniond q2 = Eigen::Quaterniond (1, 2., 3., 4.);
    Eigen::Quaterniond q3 = Eigen::Quaterniond::Identity();
    cout << q3.coeffs().transpose() << endl;
    Eigen::Quaterniond q = q1 * q2;
    //cout << (q1 * q1.inverse()).coeffs().transpose() << endl;

    cout << (q2.inverse() * (q1.inverse() * q)).coeffs().transpose() << endl;

    cout << q.coeffs().transpose() << endl;


    return 0;
}
