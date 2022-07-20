#include <iostream>
#include <vector>


using namespace std;

class A{
public:

	int mi_;
	A(int mi) : mi_(mi){
		cout << "A() start" << endl;
		}

	A(const A& tempA){	
		mi_ = tempA.mi_;
		cout << "A(const A& tempA) start" << endl;
	}

	virtual ~A(){
		cout << "~A() start" << endl;
		}

};

int main(){

	vector<A> myveca;

	myveca.reserve(10);
	for (int i = 0; i < 5; ++i){
		cout << "_------------------------------------begin------------------------------" << endl;
		myveca.push_back(A(i));
		cout << myveca.size() << endl;
		cout << myveca.capacity() << endl;
		cout << "------------------------------------end-------------------------------" << endl;

	}

	myveca.insert(myveca.begin(), A(10));
}

