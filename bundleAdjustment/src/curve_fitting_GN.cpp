#include "curve_fitting_GN.h"

void CurveFittingGN::gaussNewton() {

    for(int i = 0; i < iter; ++i){
        H_.setZero();
        b_.setZero();
        jacobian_.setZero();
        curr_cost_ = 0;
        //std::cout << H_ << std::endl;

       for(size_t j = 0; j < xs_.size(); ++j){
           double com = std::exp(a_e_ * xs_[j] * xs_[j] + b_e_ * xs_[j] + c_e_);
           double error = ys_[j] - com;
           jacobian_[0] = -xs_[j] * xs_[j] * com;
           jacobian_[1] = -xs_[j] * com;
           jacobian_[2] = - com;

           H_ += jacobian_ * jacobian_.transpose();
           b_ += - error * jacobian_;
           curr_cost_ += error * error;
       }

        last_cost_ = curr_cost_;
        if (i > 10 && last_cost_ <= curr_cost_){
            std::cout << "last cost < curr_cost, " << "cost : " << curr_cost_ << std::endl;
            break;;
       }
        std::cout << "iter " << i  << std::endl;
        std::cout << "cost : " << curr_cost_ << std::endl;
       Eigen::Vector3d delt_ = H_.ldlt().solve(b_);
       a_e_ += delt_[0];
       b_e_ += delt_[1];
       c_e_ += delt_[2];

   }

    std::cout << "cost : " << curr_cost_ << std::endl;
    std::cout << "a_t : " << a_t_ << ", b_t : " << b_t_ << ", c_t : " << c_t_ << std::endl;
    std::cout << "a_e : " << a_e_ << ", b_e : " << b_e_ << ", c_e : " << c_e_ << std::endl;
}

void CurveFittingGN::makeDataset() {
    // 构造数据集
    for(int i = 0; i < 100; ++i){
        xs_.push_back(double(i / 100.));
        double y = std::exp(xs_[i] * xs_[i] * a_t_ + xs_[i] * b_t_ + c_t_) + rng_.gaussian(w_ * w_);
        ys_.push_back(y);
        //std::cout << xs_[i] << " " << ys_[i] << std::endl;
    }
}