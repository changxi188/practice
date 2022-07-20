#include <iostream>
#include <vector>
#include <string>
#include "strblob.h"
#include "strblobptr.h"



using namespace std;
int main(){

	StrBlob b1= {"aaaa"};
	{
		StrBlob b2 = {"a", "an", "the"};	
		cout << "b2.size()" << b2.size() << endl;
		b1 = b2;
		b2.push_back("about");
		cout << "b1.size()" << b1.size() << endl;
	}

	cout << "b1.size()" << b1.size() << endl;

	return 0;
}
