#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;


int main(){	
	vector<vector<int>> vec{{2, 3}, {1, 2}, {3, 4}};

	sort(vec.begin(), vec.end());

	for (const auto &a : vec){
		cout << a[0] << endl;
	}
	cout << vec.back()[1] << endl;

	return 0;

}
