#pragma once
#include <iostream>

namespace MyClass{

class Time{
public:
	explicit Time(const int &hour, const int &min, const int &sec) : hour_(hour), min_(min), sec_(sec) {
		setMillisec();
	}

	Time(){
		hour_ = 0;
		min_ = 0;
		sec_ = 0;
	}

	Time(const Time &temptime);


	Time & operator=(const Time&);

	int getHour(){
		return hour_;
	}

	int getMillisec(){
		return millisec_;
	}

	void addHour(int n);

	~Time();

	


private:

	void setMillisec(){
		millisec_  = 1;
	}
	
	int hour_;
	int min_;
	int sec_;
	int millisec_ = 0;

};
}

