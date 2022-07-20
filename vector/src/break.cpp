#include <iostream>
#include <vector>

using namespace std;

int main(){
	cout << 111111111 << endl;
	for(int i = 0; i < 10; ++i){
		cout << i << endl;
		for(int j = 0; j < 10; ++j){
			cout << "j = " << j << endl;
			if(j == 0){
				break;
			}
		}
	}

	return 0;
}
