#include <iostream>
#include <thread>
#include <chrono>



void some_function(){

	for(int i = 0; i < 100000; ++i){
		std::cout << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}


void some_other_function(){

	for(int j = 0; j < 200000; ++j){
		std::cout << j << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}


int main(){

	std::thread t1(some_function);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::thread t2 = std::move(t1);


	//t1.join();
	if(t1.joinable()){
		std::cout << "t1 joinable" << std::endl;
		t1.join();
	}else{

		std::cout << "t2 joinable" << std::endl;
		t2.join();
	}

	return 0;
}
