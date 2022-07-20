#include <iostream>
#include <string>

using namespace std;

int main(){
	string s1 = "hello world";
	cout << s1.substr(0, 5) << endl;
	cout << s1.substr(0, 0) << endl;
	
	return 0;
}
