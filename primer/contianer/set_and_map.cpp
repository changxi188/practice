#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>


int main(){

	std::string word;

	std::map<std::string, int> word_count;
	std::set<std::string> exclude{"the", "at", "a", "b"};
	for(int i = 0; i < 10; ++i){

		std::cin >> word;
		if(exclude.find(word) == exclude.end()){
			++word_count[word];
		}
	}
	std::cout << "000000000000000000000000000000000000000000000:" << std::endl;
	word_count.insert(std::make_pair("aaa", 10));
	std::cout << word_count.size() << std::endl;
	for(const auto& word : word_count){
		std::cout << word.first << word.second << std::endl;
	}

	auto pair1 = word_count.insert(std::make_pair("aaab", 10));
	std::cout << "000000000000000000000000000000000000000000000:" << std::endl;
	// std::cout << pair1.first << std::endl;
	std::cout << pair1.second << std::endl; 

	

	return 0;
}
