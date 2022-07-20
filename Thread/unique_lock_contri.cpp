#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>


std::mutex foo, bar;


void task_a(){

	std::lock (foo, bar);
	std::unique_lock<std::mutex> lck1(foo, std::adopt_lock);
	std::unique_lock<std::mutex> lck2(bar, std::adopt_lock);

	std::cout << "task a\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "task a2\n";

	// (unlocked automatically on destruction of lck1 and lck2)

}


void task_b(){

	
	std::unique_lock<std::mutex> lck1(foo, std::defer_lock);
	std::unique_lock<std::mutex> lck2(bar, std::defer_lock);

	std::lock (lck1, lck2);
	std::cout << "task b\n";
	
	// (unlocked automatically on destruction of lck1 and lck2)

}


int main() {


	std::thread th1(task_a);
	std::thread th2(task_b);

	th1.join();
	th2.join();

	return 0;
}
