#include <iostream>
#include <thread>
#include <chrono>



void thread_task(int n){

	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout	<< "hello thread: " 
				<< std::this_thread::get_id()
				<< " paused" << n << " seconds" << std::endl;
}

int main(int argc, char** argv){


	// spwan 5 thread
	std::thread threads[5];
	for (int i = 0; i < 5; ++i){

		threads[i] = std::thread(thread_task, 3);
	}

	// start 5 thread
	for (auto &t : threads){
		t.join();
	}

	std::cout << "All threads joined. \n" << std::endl;

	return EXIT_SUCCESS;
}
