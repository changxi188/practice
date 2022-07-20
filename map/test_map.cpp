#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>


using namespace std;


int main(){
	/*

	// std::cout << 11111111 << std::endl;
	// std::unordered_map<unsigned long, string> test_map;
	std::map<unsigned long, string> test_map;
	std::cout << test_map.size() << std::endl;
	test_map.insert(std::make_pair(1, "cheng"));
	test_map.insert(std::make_pair(2, "chang"));
	test_map.insert(std::make_pair(4, "ha"));
	test_map.insert(std::make_pair(6, "hahaha"));
	test_map.insert(std::make_pair(5, "haha"));
	test_map.insert(std::make_pair(3, "xi"));

	std::cout << test_map.size() << std::endl;
	for(auto& m : test_map){
		std::cout << m.first << " : " << m.second << std::endl;
	}

	for(auto iter = test_map.begin(); iter != test_map.end();){
		if(iter->first == 1){
			std::cout << iter->second << std::endl;
			iter = test_map.erase(iter);
			continue;
		}
		++iter;
	}
	std::cout << "hhhhhhhhhhhhhh" << std::endl;
	for(auto& m : test_map){
		std::cout << m.first << " : " << m.second << std::endl;
	}

	std::cout << "hhhhhhhhhhhhhh" << std::endl;
	std::cout << test_map.size() << std::endl;
	// std::cout << test_map.capacity() << std::endl;
	*/
	

	std::vector<int> test_vec{1, 2, 3, 4, 5, 6};

	for(auto & i : test_vec){
		std::cout << i << std::endl;
	}	

	for(auto iter = test_vec.begin(); iter != test_vec.end();){
		if(*iter == 1){
			test_vec.erase(iter);
		}
		iter++;
	}

	std::cout << "hhhhhhhhhhhhhhhhhhhhh " << std::endl;

	for(auto & i : test_vec){
		std::cout << i << std::endl;
	}	


	return 0;
}

