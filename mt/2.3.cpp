#include <iostream>
#include <vector>
#include <string>
#include <thread>

using namespace std;

class A{
public:
	int myi;
	A(const int &i) : myi(i) { cout << "构造函数执行" << endl;}
	A(const A &a) : myi(a.myi) { cout << "拷贝构造函数执行" << endl;}
	~A() {cout << "析构函数执行" << endl;}
};

void myprint(const int i, const A &a){

	cout << "thread1 start " << endl;

	cout << "thread2 end" << endl;
}

int main(){
	
	int myi = 6;

	int mysecond = 7;

	thread mytobj(myprint, myi, A(mysecond));
	//mytobj.join();
	mytobj.detach();

	return 0;
}
