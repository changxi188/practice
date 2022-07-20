#include <iostream>
#include <thread>
#include <vector>


/*
class TA{
public:
	void operator()(){
		std::cout << "thread TA start" << std::endl;

		std::cout << "thread TA endl;" << std::endl;

	}

private:

};
*/


void myprint(const int& i, char* mybuff){
	while(true){
	std::cout << i << std::endl;
	
	std::cout << mybuff << std::endl;
	}

}

int main(){
	/*
	TA ta;
	std::thread th1(ta);
	th1.join();
	*/
	int mvar = 1;
	int& mvary = mvar;
	char mybuff[] = "i love china";


	std::thread th2(myprint, mvar, mybuff);

	th2.detach();

	return 0;
}
