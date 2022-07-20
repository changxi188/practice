#include <iostream>			// std::cout 
#include <thread>			// std::thread
#include <mutex>			// std::mutex std::lock_guard
#include <stdexcept>		// std::logic_error



std::mutex mtx;

void print_even(int n){

	if(n % 2 == 0) std::cout << n << " is even" << std::endl;
	else throw (std::logic_error("not even"));

}


void print_thread_id(int n){

	try{
		std::lock_guard<std::mutex> lck(mtx);
		print_even(n);
	}
	catch(std::logic_error&){
		std::cout << "exception caught \n";
	}

}




int main(int argc, char** argv){


	int n = 0;
	std::thread threads[10];
	for (int i = 0; i < 10; ++i){
		
		threads[i] = std::thread(print_thread_id, i + 1);

	}

	for (auto &t : threads){
	
		t.join();

	}

	return 0;

}

