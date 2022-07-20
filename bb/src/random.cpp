#include <iostream>
#include <random>
#include <map>
#include <vector>
#include <string>

int main(){

	std::random_device rd;
	std::default_random_engine generator_(rd());
	std::normal_distribution<double> noise(0.0, 1.0);


	std::map<double, size_t> num_count;
	for(size_t i = 0; i != 200; ++i){

		double v = noise(generator_);
		++num_count[v];
	}
	std::cout << num_count << std::endl;

}
