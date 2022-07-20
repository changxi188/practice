#include <iostream>
#include <mutex>
#include <thread>


std::mutex mtx;



void print_fifty(char c){

	// default constructed
	std::unique_lock<std::mutex> lck;
	// move assigned
	// 这里解释以下,由于std::unique_lock<std::mutex>(mtx)是一个右值, 所以这里调用了move构造函数来初始化lck
	lck = std::unique_lock<std::mutex>(mtx);

	for (int i = 0; i < 50; ++i){
		std::cout << c;
	}

	std::cout << '\n';


}


int main(){

	std::thread th1(print_fifty, 'x');
	std::thread th2(print_fifty, 'y');

	th1.join();
	th2.join();

	return 0;
}
