#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


std::mutex mtx;


void print_star(){

	std::unique_lock<std::mutex> lck(mtx, std::try_to_lock);
	if (lck.owns_lock()){
		std::cout << "*";
	}
	else
		std::cout << "x";

}


int main(){

	std::vector<std::thread> threads;

	for (int i = 0; i < 500; ++i){
		threads.emplace_back(print_star);
	}

	for (auto &t : threads){
		t.join();
	}

	
	return 0;
}
