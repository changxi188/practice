#include <iostream>
#include "Men.h"
#include "Women.h"

class A {
public:
	A(int i) : ia_(i) {}

private:
	int ia_;
};

class B final : public A{
public:
	B(int i, int j, int k) : A(i), ib_(j) {}

private:
	int ib_;

};


int main(){

	//Men mymen;

	//Human *pHuman = new Men;

	//Men mymen;

	/*
	A a(1);
	B b(1, 2, 3);
	*/

	/*
	Human *pHuman = new Men();
	Human &q = *pHuman;
	*/

	/*
	Human *pHuman = new Men();
	Human &q = *pHuman;
	*/

	Men men;
	Human human(men);
	Human human2;
	human2 = men;
		

	return 0;
}
