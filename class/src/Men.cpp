#include "Men.h"

using namespace std;
Men::Men(){

	//cout << "Man() start" << endl;
}


void Men::sameNameFun(int i){

	cout << "Men::sameNameFun() start" << endl;
	fun_pro();
}

void Men::eat(){
	cout << "Men like eat" << endl;
}	

/*
void Men::sport(){
	cout << "Men like run" << endl;
}
*/

void Men::manfun() const {
	cout << "test" << endl;
}

void Men::testfunc(){
	cout << "testfunc() start" << endl;
}

Men::~Men(){
	//cout << "Men::~Men start" << endl;
}	


