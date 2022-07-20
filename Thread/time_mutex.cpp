#include <iostream>		// std::cout
#include <chrono>		// std::chrono::milliseconds
#include <thread>		// std::thread
#include <mutex>		// std::timed_mutex


std::timed_mutex mtx;


void fireworks(){
	
	// waiting to get a lock: each thread prints "-" every 200ms;
	while( !mtx.try_lock_for(std::chrono::milliseconds(200))){
		std::cout << "-";
	}

	// got a lock! -wait for 1s, then this thread prints "*"

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "*\n";
	mtx.unlock();
}


int main(int argc, char** argv){


	std::thread threads[11];

	for (int i = 0; i < 11; ++i){

		threads[i] = std::thread(fireworks);

	}

	for (auto &t : threads){

		t.join();
	}

	return 0;
}
