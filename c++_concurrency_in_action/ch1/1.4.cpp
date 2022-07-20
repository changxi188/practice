#include <iostream>
#include <thread>


using namespace std;

void HelloWorld(){
	cout << "hello world, I am t1 " << endl;
}


class A{

	public:
		A(int i ) : i_(i){
			cout << "A(int i) start" << endl;
		}


	private:
		int i_ = 0;
};

int main(){
	A a1(1);
	thread t1(HelloWorld);

	cout << HelloWorld << endl;

	//t1.join();
}

