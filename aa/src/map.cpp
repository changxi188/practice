#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <memory>
#include <Eigen/Core>
#include <Eigen/Geometry>


int main(){
	typedef Eigen::Matrix<double, 3, 3> Rotation;
	
	typedef std::unordered_map<unsigned long, Rotation> RotationsType;

	RotationsType Rs;
	for (int i = 0; i < 5; ++i){
		
		Rs.insert(std::make_pair(i, Rotation::Identity()));

	}	

	for (int i = 5; i < 10; ++i){

		Rs.insert(std::make_pair(i, Rotation::Identity() * 2));

	}	


	
	for (auto iter = Rs.begin(); iter != Rs.end(); ++iter){
		
		std::cout << iter->second << std::endl;

		std::cout << 111111111111 << std::endl;
	}	

	for (auto iter = Rs.begin(); iter != Rs.end(); ++iter){
		
		Rs.erase(iter);
		std::cout << iter->second << std::endl;
	}


	return 0;
}
