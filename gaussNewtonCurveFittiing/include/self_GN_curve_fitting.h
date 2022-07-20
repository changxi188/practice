#pragma once
#ifndef __SELF_GN_CURVE_FITTING_H__
#define __SELF_GN_CURVE_FITTING_H__
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>

class SelfGN{
public:
	SelfGN(const double& a_t, const double& b_t, const double& c_t) :
			a_t_(a_t), b_t_(b_t), c_t_(c_t) {}
	
	void buildDataset();	

	void GN();

	void getResult(double& a, double& b, double& c);

private:	

	// 真实结果
	double a_t_, b_t_, c_t_;
	
	// 迭代次数
	int iter_n_ = 100;

	// 数据集个数
	int dataset_n_ = 100;

	// 高斯分布的标准差sigma
	double sigma_ = 1;
	double inv_sigma_ = 1 / sigma_;


	// 估计的结果
	double a_e_ = 1, b_e_ = 1 , c_e_ = 1;

	// dataset
	std::vector<double> y_;
	std::vector<double> x_;

};

inline
void SelfGN::getResult(double& a, double& b, double&c){
	a = a_e_;
	b = b_e_;
	c = c_e_;
}
#endif

