#include <iostream>


#include "Human.h"
#include "Men.h"


using namespace std;


int main(){

	Human *pHuman = new Men(1);
	pHuman->eat();

	delete pHuman;

	
	return 0;
}
