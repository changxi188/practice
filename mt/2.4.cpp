#include <iostream>
#include <vector>
#include <string>
#include <thread>


using namespace std;


void myprint(int tnum){
	
	cout << "thread " << tnum << " start" << endl;
	cout << "thread " << tnum << " end" << endl;

}


int main(){

	vector<thread> Vthread;	

	for(int i = 0; i < 10; ++i){

		Vthread.push_back(thread(myprint, i));

	}

	for(auto iter = Vthread.begin(); iter!= Vthread.end(); ++iter){

		iter->join();

	}

	cout << "I love c++ " << endl;

	return 0;
}
