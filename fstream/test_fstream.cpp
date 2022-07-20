#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sophus/so3.hpp>
#include <sophus/se3.hpp>
#include <Eigen/Core>

using namespace std;


int main(){

	ofstream write_file("../test_sophus.txt", ios::ate);
	Eigen::Matrix<double, 3, 1> t;
	t << 1, 2, 3;
	Sophus::SE3d pose(Sophus::SO3d(), t);

	cout  << pose.matrix() << endl;

	cout << pose.matrix()(0,0) << endl;

	write_file.close();

	return 0;
}
