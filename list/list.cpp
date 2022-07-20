#include <iostream>
#include <list>

using namespace std;

int main(){
	std::list<int> obs;
	obs.push_back(0);
	obs.push_back(1);
	obs.push_back(2);
	obs.push_back(3);
	obs.push_back(4);
	obs.push_back(5);
	obs.push_back(6);


	for(auto iter = obs.begin(); iter != obs.end(); ++iter){
		cout << *iter << endl;
	}

	auto dele = obs.begin();

	for(auto iter = obs.begin(); iter != obs.end(); ++iter){
		if(*iter == 3){
			obs.erase(iter);
			break;
		}
	}

	for(auto iter = obs.begin(); iter != obs.end(); ++iter){
		cout << *iter << endl;
	}


	return 0;
}



