#include <iostream>
#include <memory>


using namespace std;

void subFunc(){

	int a = 1;
	cout << "subFunc() start" << endl;
}


class Gcc{
public:
	Gcc(int gcc, int a) : gcc_(gcc), a_(a){}

	void classFunc(){
		std::cout << "classFunc() start" << endl;
	}

private:
	int gcc_;
	int a_;

};

int main(){
	
	int a = 0;

	std::cout << "hello world" << endl;
	subFunc();

	std::shared_ptr<Gcc> gcc = std::make_shared<Gcc>(1, 0);	
	gcc->classFunc();
	
	return 0;
}
