#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        vector<vector<int>> new_matrix;
        int len = matrix.size();
        vector<int> new_row;
        for (int i = 0; i < len; ++i){
            for (auto riter = matrix.rbegin(); riter != matrix.rend(); ++riter){
                new_row.push_back((*riter)[i]);
            }
            new_matrix.push_back(new_row);
			new_row.clear();
        }
		matrix = new_matrix;
    }
};

int main(){
	Solution solve;
	//auto solve = std::make_shared<Solution>();

	vector<vector<int>> test_matrix1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	for (const auto &rows : test_matrix1){
		for (const auto &elem : rows){
			cout << elem;
		}
		cout << endl;
	}
	

	
	solve.rotate(test_matrix1);
	//solve->rotate(test_matrix1);

	for (const auto &rows : test_matrix1){
		for (const auto &elem : rows){
			cout << elem;
		}
		cout << endl;
	}
	
	return 0;

}
