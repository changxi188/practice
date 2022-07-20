#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>


using namespace std;

class A{
public:
	A() {
		cout << "A::A() start" << endl;
	}

	~A() {
		cout <<"~A::A() start" << endl;
	
	}
};

shared_ptr<int> make(int value){

	return shared_ptr<int>(new int(value));
}

int main(){

	/*
	A *pa = new A();
	delete pa;
	*/

	/*
	int *p = new int;
	delete p;
	*/

	/*
	int *p1 = new int;
	cout << *p1 << endl;
	delete p1;

	int *p = new int[3]();
	cout << *(p+2) << endl;
	delete[] p;
	*/

	/*
	A *pA = new A[2]();
	delete[] pA;
	*/

	/*
	shared_ptr<int> pi(new int(10));
	cout << *pi << endl;

	shared_ptr<int> pi2 = make(1);
	cout << *pi2 << endl;

	shared_ptr<int> p2(make_shared<int> (100));
	cout << *p2 << endl;

	shared_ptr<string> p3(make_shared<string>(5, 'a'));
	cout << *p3 << endl;

	shared_ptr<int> p4 = make_shared<int>();
	p4 = make_shared<int>(400);

	auto p5 = make_shared<string>(5, 'b');
	cout << *p5 << endl;
	*/


	return 0;
}
