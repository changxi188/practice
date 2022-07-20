#include <iostream>
#include <vector>

using namespace std;

int main(){

	vector<int> ii(5, 0);
	for (const auto &i : ii)
		std::cout << i << "\t";
	std::cout << std::endl;
	int n = 1;
	/*
	for (auto it = ii.begin(); it != ii.end(); ++it){
		ii.push_back(n);
		++n;
		cout << n << "\t";

	}

	*/

}
