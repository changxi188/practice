#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>


using namespace std;

int main(){
	/*
	Eigen::Vector3d p, t2, t1;
	p << 0.5, 0, 0.2;
	t1 << 0.3, 0.1, 0.1;
	*/

	Eigen::Quaterniond q1 = Eigen::Quaterniond(0, 2., 3., 4.).normalized();
	cout << q1.coeffs().transpose() << endl;

	cout << (q1 * q1).coeffs() << endl;

	cout << 1 << std::endl;	

	return 1;
}

