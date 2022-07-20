#include <iostream>
#include <string>
#include <vector>

#include "Human.h"
#include "Men.h"
#include "Women.h"

using namespace std;


void fun(const Men& men){

	men.manfun();
}

int main(){
	
	/*
	Men man;

	man.m_pub = 12;
	man.fun_pub();
	//man.fun_pro();

	man.sameNameFun();
	man.sameNameFun(10);

	*/

	/*
	Human *phuman = new Human();
	Men *pman = new Men();
	*/


	/*
	Human *phuman = new Men();
	phuman->eat();
	phuman->Human::eat();
	*/
	
	/*
	Women *pWoman = new Women();
	delete pWoman;
	*/

	/*
	Human *pHuman = new Women();
	pHuman->sport();
	delete pHuman;
	*/

	/*
	Men man;
	fun(man);
	*/

	/*
	Human *pHuman1 = new Men();
	Men *p = (Men *)(pHuman1);
	p->testfunc();
	delete p;
	*/

	/*
	Human *pHuman = new Men;
	Men *pmen = dynamic_cast<Men *>(pHuman);
	if (pmen != nullptr){
		pmen->testfunc();
	}
	delete pmen;
	*/

	/*
	Human *pHuman = new Men;
	Human &p = *pHuman;
	try{
		Men &q = dynamic_cast<Men &> (p);
		q.testfunc();
		cout << "cast succ " << endl;
	}
	catch(std::bad_cast){
		cout << " cast fail" << endl;
	}
	*/

	/*
	Human *pHuman = new Men;
	Human &p = *pHuman;
	cout << typeid(*pHuman).name() << endl;
	cout << typeid(p).name() << endl;
	*/

	/*
	Human *pHuman = new Men;
	const type_info& tp = typeid(*pHuman);
	cout << tp.name() << endl;
	*/


	return 0;
}
