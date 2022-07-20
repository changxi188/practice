#include <iostream>
#include <string>
#include <vector>


using namespace std;

/*
class TestInt{
public:
	
	TestInt(int i) : m_v(i) {	
		if (m_v > 100){
			m_v = 100;
		} else if (m_v < 0){
			m_v = 0;
		}
	}

private:
	int m_v;

};
*/


class CT{
public:
	void ptfunc(int tempValue) { cout << "void ptfunc(int tempValue) start, value = " << tempValue << endl;}
	virtual void virtualfunc(int tempValue) { cout << "virtual void virtualfunc(int tempValue) start, value = " << tempValue << endl;}
	static void staticfunc(int tempValue) {cout << "static void staticfunc(int tempvlaue) start, vaule = " << tempValue << endl;}

	int m_a;
	static int m_b;

};

int CT::m_b = 10;

int main(){
	/*	
	TestInt ti = 12;
	TestInt ti2(12);
	*/

	/*
	void (CT::* myfpoint)(int);
	myfpoint = &CT::ptfunc;

	CT ct, *pct;
	pct = &ct;
	
	(ct.*myfpoint)(100);
	(pct->*myfpoint)(200);

	void (CT::*myfpointvirtual)(int) = &CT::virtualfunc;

	(ct.*myfpointvirtual)(100);
	(pct->*myfpointvirtual)(200);


	void(*staticfunc)(int) = &CT::staticfunc;
	staticfunc(100);
	*/

	CT ct, *pct;
	pct = &ct;

	int CT::*mp = &CT::m_a;

	ct.*mp = 180;
	cout << ct.*mp << endl;
	cout << ct.m_a << endl;

	int *stcp = &CT::m_b;
	*stcp = 111;
	cout << *stcp << endl;
	cout << ct.m_b << endl;



	return 0;
}
