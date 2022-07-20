#include <iostream>			// std::cout
#include <thread>			// std::thread
#include <mutex>			// std::mutex

volatile int counter(0);	// non-atomic counter
std::mutex mtx;				// locks access to counter


void attempt_10k_increase(){

	for (int i = 0; i < 1000; ++i){
		
		if (mtx.try_lock()){
			++counter;
			mtx.unlock();
		}
	}

}


int main(int argc, char** argv){

	//std::thread threads(attempt_10k_increase);

	std::thread t[10];
	for (int i = 0; i < 10; ++i){
		
		t[i] = std::thread(attempt_10k_increase);

	}
	//threads.join();

	for (auto &tt : t){
		tt.join();
	}

	std::cout << counter <<  std::endl;


	return EXIT_SUCCESS;
}
