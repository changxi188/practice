#include "B.h"
#include "A.h"

void B::callCAF(const int& x, A& a){

	a.i_x = x;
	std::cout << a.i_x << std::endl;
}
