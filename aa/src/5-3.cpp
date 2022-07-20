#include <iostream>
#include <memory>

using namespace std;


shared_ptr<int> myfunc(shared_ptr<int> temp){

	return temp;
}

int main(){

	/*
	shared_ptr<int> p5 = make_shared<int>(1);
	auto p6(p5);

	auto p7 = myfunc(p6);
	cout << p7.use_count() << endl;
	cout << p7.unique() << endl;
	*/


	shared_ptr<int> pi(new int(100));
	pi.reset();
	if (pi == nullptr){
		cout << "pi is null" << endl;
	}

	shared_ptr<int> pj(new int(100));
	pj.reset(new int(1));
	cout << *pj << endl;
	return 0;
}
