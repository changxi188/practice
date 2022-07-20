#include <Eigen/Dense>
#include <iostream>


int main(){
	
	std::cout << " begin " << std::endl;

	Eigen::Matrix4d T(4, 4);
	T << 1, 2, 3, 4,
		 5, 6, 7, 8,
		 9,10,11,12,
		13,14,15,16;
	
	std::cout << T << std::endl;

	Eigen::MatrixXd a = T.block(0, 0, 2, 2);
	std::cout << a << std::endl;


	// 输出向量
	Eigen::Matrix<double, 6, 1> V6d(6);
	V6d << 1, 2, 3, 4, 5, 6;
	std::cout << V6d << "\t";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << V6d.head(3) << "\t";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << V6d.tail(3) << "\t";
	std::cout << std::endl;

	
}
