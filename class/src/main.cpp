#include <iostream>
#include <string>
#include <vector>
#include "Time.h"


using namespace std;
using namespace MyClass;


int main(){

	Time time1(1, 2, 3);
	Time time2;
	cout << time1.getMillisec() << endl;
	cout << time2.getHour() << endl;
	//time1.addHour(10);
	//cout << time1.getHour() << endl;
	Time time3(time1);
	Time time4 = time3;

	time4 = time3;

	time4.operator=(time3);
	/*
	if (time3 == time4){
		cout << "aaa " << endl;
	}
	*/	

	Time* pMyTime5 = new Time;
	Time* pMyTime6 = new Time(1, 2, 3);


	delete pMyTime5;
	delete pMyTime6;

	return 0;
}
