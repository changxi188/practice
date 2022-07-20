#include <iostream>
#include <thread>
#include <string>


void thread_task(const std::string &a){
	std::cout << a << std::endl;
}


int main(){

	std::thread t(thread_task, "hello");
	t.join();
	return EXIT_SUCCESS;

}
