#include "self_GN_curve_fitting.h"

using namespace std;

void SelfGN::buildDataset(){
	cv::RNG rng;
	//double x, y;
	for (int i = 0; i < dataset_n_; ++i){
		double x = i / 100.;
		double y = exp(a_t_ * x * x + b_t_ * x + c_t_) + rng.gaussian(sigma_ * sigma_);
		x_.push_back(x);
		y_.push_back(y);
	}
}


void SelfGN::GN(){
	double cost = 0, last_cost = 0;
	for (int i = 0; i < iter_n_; ++i){
		Eigen::Matrix<double, 3, 3> H = Eigen::Matrix3d::Zero();
		Eigen::Matrix<double, 3, 1> b = Eigen::Vector3d::Zero();
		cost = 0;
		for (int j = 0; j < dataset_n_; ++j){	
			double jaco_com = exp(a_e_ * x_[j] * x_[j] + b_e_ * x_[j] + c_e_);

			double error = y_[j] - jaco_com;

			Eigen::Matrix<double, 3, 1> jacobi;

			jacobi[0] = -x_[j] * x_[j] * jaco_com;
			jacobi[1] = -x_[j] * jaco_com;
			jacobi[2] = -jaco_com;

			H += jacobi * jacobi.transpose();
			b += -jacobi * error;
			cost += error;
		}
		/*
		if (i > 0 && cost >= last_cost){
			std::cout << "cost < last cost" << std::endl;
			std::cout << "iteration : " << i << "\t" << "cost : " <<  cost << "\t" << endl;
			break;
		}
		*/

		if (i > 0 && cost * cost < 0.058 * 0.058){
			std::cout << "|cost| < 0.058" << std::endl;
			std::cout << "iteration : " << i << "\t" << "cost : " <<  cost << "\t" << endl;
			break;
		}

		last_cost = cost;
		std::cout << "iteration : " << i << "\t" << "cost : " <<  cost << "\t" << endl;
		Eigen::Matrix<double, 3, 1> delta_gama = H.ldlt().solve(b);
		a_e_ += delta_gama[0];
		b_e_ += delta_gama[1];
		c_e_ += delta_gama[2];
	}
}

