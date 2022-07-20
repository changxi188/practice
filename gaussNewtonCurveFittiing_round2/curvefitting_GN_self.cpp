#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>



int main(){
	cv::RNG rng;
	double a_t = 1, b_t = 2, c_t = 3;
	double a_e = 3, b_e = 4, c_e = 2;

	double sigma = 1;
	double inv_sigma = 1 / sigma;

	// 数据集数量
	int N = 100;
	std::vector<double> x_, y_;

	// 迭代次数
	int iter_n = 10;

	for (int i = 0; i < N; ++ i){
		x_.push_back(i / 100.);
		y_.push_back( std::exp(a_t * x_[i] * x_[i] + b_t * x_[i] + c_t) + rng.gaussian(sigma * sigma));
	}

	for (int i = 0; i < iter_n; ++ i){
		// Eigen::Matrix<double, 3, 3> H 默认初始化为随机数, 所以这里要设置为0
		Eigen::Matrix<double, 3, 3> H = Eigen::Matrix3d::Zero();
		//std::cout << H << std::endl;
		Eigen::Matrix<double, 3, 1> b = Eigen::Vector3d::Zero();
		double cost = 0;

		for (int j = 0; j < N; ++j){
			double jac_com = std::exp(a_e * x_[j] * x_[j] + b_e * x_[j]  + c_e);
			double error = y_[j] - jac_com;
			Eigen::Matrix<double, 3, 1> jacobian;
			jacobian[0] = -x_[j] * x_[j] * jac_com;
			jacobian[1] = -x_[j] * jac_com;
			jacobian[2] = -jac_com;	

			H += jacobian * inv_sigma * inv_sigma * jacobian.transpose();
			b += - jacobian * inv_sigma * inv_sigma * error;
			cost += error * error;
		}

		Eigen::Vector3d delta = H.ldlt().solve(b);
		a_e += delta[0];
		b_e += delta[1];
		c_e += delta[2];
		std::cout << "iteration : " << i << "\t" <<  "chi2 : " << cost << std::endl;
	}
	std::cout << a_e << " " << b_e << " " << c_e << std::endl;

	return 0;
}
