#ifndef __CURVE_FITTING_H__
#define __CURVE_FITTING_H__
#include "common_include.h"

class CurveFittingGN{
public:
    typedef std::shared_ptr<CurveFittingGN> Ptr;

    CurveFittingGN(){
        makeDataset();
    };

    CurveFittingGN(double a_e, double b_e, double c_e)
        : a_e_(a_e), b_e_(b_e), c_e_(c_e){

        makeDataset();
    };


    void gaussNewton();

private:
    void makeDataset();

private:

    cv::RNG rng_;
    double a_t_ = 1., b_t_ = 2., c_t_ = 3.;
    double a_e_ = 5., b_e_ = -5., c_e_ = 5.;
    Eigen::Matrix<double, 3, 3> H_ ;
    Eigen::Matrix<double, 3, 1> b_;
    Eigen::Matrix<double, 3, 1> jacobian_;
    double curr_cost_ = 0, last_cost_ = 0;
    //Eigen::Matrix<double, 3, 1> delt_;

    // 数据集
    std::vector<double> xs_, ys_;
    double w_ = 1;
    int iter = 100;

};



#endif