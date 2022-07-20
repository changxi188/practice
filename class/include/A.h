#pragma once
#include <iostream>
#include "B.h"

class A{
friend void B::callCAF(const int&, A&);
private:
	int i_x;

};
