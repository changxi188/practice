#include <iostream>
#include <string>
#include <vector>


using namespace std;

class A{
public:
	A() {
		cout << "A" << endl;
	}
};

int main(){

	/*
	string *mystr = new string("i love coding");
	vector<int> *pvec = new vector<int>();

	string *mystr3 = new string();
	int *pointi2 = new int();
	delete mystr;
	delete pvec;
	delete mystr3;
	delete pointi2;
	*/

	/*
	string *mystr2 = new string(5, 'a');
	auto mystr3 = new auto(mystr2);
	delete mystr2;

	A *pa = new A();

	delete pa;
	*/

	/*
	const int *pi = new const int(200);
	cout << *pi << endl;
	delete pi;
	*/
	/*
	string *mystr = new string(10, 'a');
	cout << mystr->c_str() << endl;
	delete mystr;
	*/

	/*
	int *p = new int();
	int *p2 = p;
	delete p2;
	delete p;
	*/

	int *p = new int(300);
	cout << *p << endl;
	*p = 400;
	cout << *p << endl;
	delete p;
	p = nullptr;	// good, this is a good xiguan



	return 0;
}
