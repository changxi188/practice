#pragma once
#include "Human.h"
#include <iostream>

class Men : public Human{
public:
	
	friend void fun(const Men& men);
	
	Men();

	using Human::sameNameFun;
	void sameNameFun(int i);


	virtual void eat() override;

	//virtual void sport() override;

	void testfunc();

	~Men();

private:
	void manfun() const;


};
