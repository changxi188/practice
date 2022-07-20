#include <iostream>
#include <Eigen/Core>
#include <memory>
#include "self_GN_curve_fitting.h"

using namespace std;

int main(){

	// 非线性公式, w ~ N(0, sigma)
	// y = exp(a * x * x + b * x + c) + w 

	double a_t = 1., b_t = 2., c_t = 3.;
	double a_e, b_e, c_e;
	auto gn = std::make_shared<SelfGN>(a_t, b_t, c_t);

	// 构建数据集
	gn->buildDataset();
	// 开始GN迭代优化
	gn->GN();
	// 获取结果
	gn->getResult(a_e, b_e, c_e);

	std::cout << a_e << " " << b_e << " " << c_e << std::endl;


	return 0;
}
