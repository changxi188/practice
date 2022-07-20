#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;


typedef unordered_map<int, string> string_map;

int main(){

	string_map test_map;

	for (size_t i = 0; i < 5; ++i){
		test_map.insert(std::make_pair(i, "a"));
	}
	std::cout << "test_map.size() " << test_map.size() << std::endl;

	/*
	for (size_t i = 0; i < test_map.size(); ++i){
		std::cout << test_map[i].cend << std::endl;
	}
	*/

	/*
	for (const auto &iter : test_map){
		std::cout << iter.first << std::endl;
		std::cout << iter.second << std::endl;

	}
	*/

	for(auto iter = test_map.begin(); iter != test_map.end();){
		if (iter->first == 2){
			iter = test_map.erase(iter);
		}else {
			iter++;
		}
	}

	for (const auto &iter : test_map){
		std::cout << iter.first << std::endl;
		std::cout << iter.second << std::endl;
	}


	std::cout << "test_map.size() " << test_map.size() << std::endl;


	return 0;
}
