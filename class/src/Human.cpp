#include "Human.h"

using namespace std;

Human::Human(){

	//cout << "Human::Human() start" << endl;
}

Human::Human(int){

	cout << "Human(int) start" << endl;
}

Human::Human(const Human& tempHuman){
	// ...
}

/*
Human& Human::operator=(const Human& tempHuman){

	// ...
	return *this;
}
*/

Human& Human::operator=(const Human& tempHuman){
		
	return *this;
}		


void Human::sameNameFun(){

	cout << "Human::sameNameFun() start" << endl;
}

void Human::eat(){
	cout << "Human like eat" << endl;
}

Human::~Human(){
	//cout << "Human::~Human start" << endl;
}
