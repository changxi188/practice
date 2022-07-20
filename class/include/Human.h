#pragma once

#include <iostream>


class Human{

public:
	Human();
	Human(int);
	Human(const Human& tempHuman);

	Human& operator=(const Human& tempHuman);

	int m_pub;
	void fun_pub(){};

	void sameNameFun();


	void humanfun(){};
	
	virtual void eat();

	//virtual void sport() = 0;

	virtual ~Human();

protected:
	int m_pro;
	void fun_pro(){}

private:
	int mAge;
	char mName[100];

	int m_pri;
	void fun_pri(){}
};
