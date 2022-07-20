#include "Time.h"

using namespace std;

namespace MyClass{

void Time::addHour(int n){
	
	hour_ += n;
}


Time::Time(const Time &temptime){ 
	cout << "copy function start" << endl;	
}

Time& Time::operator=(const Time& temptime){
	
	cout << " operator= start" << endl;
	return *this;
}

Time::~Time(){
	
	std::cout << " ~Time()  run" << endl; 
}

}
