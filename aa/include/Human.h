#pragma once
#include <iostream>



class Human{
public:
	Human(int temp) : h_i_(temp){}

	virtual void eat();


	virtual ~Human(){}


private:
	int h_i_;

};


