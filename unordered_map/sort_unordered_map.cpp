#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>



using namespace std;

/*
bool sort_by_id(int i, int j){
	return i < j;

}
*/

int main(){

	unordered_map<int, string> test_um;
	test_um.insert(make_pair(1, "a"));
	test_um.insert(make_pair(2, "b"));
	test_um.insert(make_pair(3, "c"));
	test_um.insert(make_pair(4, "d"));

	
	// sort(test_um.begin(), test_um.end(), sort_by_id);
	//
	std::map<int, string> test_sorted_m(test_um.begin(), test_um.end());

	for(auto &t : test_sorted_m){
		cout << t.first <<endl;

	}

	std::cout << "111111 " << std::endl;

	for(auto &t : test_um){

		cout << t.first << endl;
	}

	return 0;
}
