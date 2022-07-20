#include <iostream>
#include <vector>
#include <string>


using namespace std;


int main(){
	
	int a = 1;
	int &b = a;

	const int &c = b;

	int &&d = 1;


	int i = 10;
	int &&ri = std::move(i);
	

	int &&ri2 = 100;
	int &&ri8 = std::move(ri2);




}
