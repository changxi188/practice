#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Solution{
public:
	void setZeros(vector<vector<int>>& matrix){
		int rows_len = matrix.size();
		int cols_len = matrix[0].size();
		auto new_matrix = matrix;
		for(int i = 0; i < rows_len; ++i){
			for (int j = 0; j < cols_len; ++j){
				if(matrix[i][j] == 0){
					// make matrix[i][*] = 0;
					for (auto &row : new_matrix[i]){
						row = 0;
					}

					// make matrix[*][j] = 0;
					for (auto &col : new_matrix){
						col[j] = 0;
					}
				}
			} 
		}

		matrix = new_matrix;
	}

};

int main(){
	//Solution solve;
	auto solve = std::make_shared<Solution>();

	vector<vector<int>> test_matrix1{{1, 2, 3}, {4, 0, 6}, {7, 8, 9}};

	for (const auto &rows : test_matrix1){
		for (const auto &elem : rows){
			cout << elem << "\t";
		}
		cout << endl;
	}
	

	
	//solve.rotate(test_matrix1);
	solve->setZeros(test_matrix1);

	// show result
	cout << "show result" << endl;
	for (const auto &rows : test_matrix1){
		for (const auto &elem : rows){
			cout << elem << "\t";
		}
		cout << endl;
	}
	
	return 0;

}
