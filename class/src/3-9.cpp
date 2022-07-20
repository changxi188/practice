#include <iostream>
#include <string>
#include <vector>
#include "A.h"
#include "B.h"

using namespace std;


/*
class A{

friend class B;
private:
	int i1;
};


class B{
public:
	void callCAF(const int& i, A& a){
		a.i1 = i;

		cout << a.i1 << endl;
	}


};
*/


int main(){

	A a;
	B b;
	b.callCAF(10, a);


	return 0;
}

