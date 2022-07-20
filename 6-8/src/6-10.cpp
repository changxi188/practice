#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <future>
#include <condition_variable>
#include <atomic>


using namespace std;

//
//int mythread(int temp){
//	cout << "mythread(int temp) start, thread id = " << this_thread::get_id() << endl;
//	temp++;
//	std::chrono::milliseconds dura(2000);
//	this_thread::sleep_for(dura);
//
//	cout << "mythread(int temp) end" << endl;
//
//	return temp;
//}
//

std::atomic<int> g_mycount(0);
std::mutex g_my_mutex;

std::atomic<bool> g_ifend(false);

void mythread(){


	for(int i = 0; i < 10000000; ++i){

		//std::unique_lock<mutex> sbgurad(g_my_mutex);
		g_mycount++;
	}
	
}
void mythread2(){
	
	std::chrono::milliseconds dura(1000);
	while(!g_ifend){
		cout << "thread id : " << this_thread::get_id() << " start" << endl;
		this_thread::sleep_for(dura);
	}

	cout << "thread id : " << this_thread::get_id() << " end" << endl;
	return;

}

int main(){

//	cout << "main thread start, thread id = " << this_thread::get_id() << endl;
//
//	std::future<int> fu1 = std::async(mythread, 1);
//	cout << "continue... " << endl;
//
//	//int result = fu1.get();
//	//cout << result << endl; 
//
//	std::future_status status = fu1.wait_for(std::chrono::seconds(3));
//	if(status == std::future_status::timeout){
//		cout << "thread does not over" << endl;
//		cout << fu1.get() << endl;
//	}
//	else if(status == std::future_status::ready){
//		cout << "thread over " << endl;
//		cout << fu1.get() << endl;
//	}
//	else if (status == std::future_status::deferred){
//	
//		cout << "thread deferred " << endl;
//		cout << fu1.get() << endl;
//	}
//
//	cout << "main thread end" << endl;
//
//	thread mt1(mythread);
//	thread mt2(mythread);
//	mt1.join();
//	mt2.join();
//	cout << g_mycount << endl;
	
	cout << "main thread id : " << this_thread::get_id() << endl;
	
	thread mt1(mythread2);
	thread mt2(mythread2);
	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	g_ifend = true;


	mt1.join();
	mt2.join();


	return 0;
}
