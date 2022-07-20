#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <future>



using namespace std;

int mythread(){


	cout << "mythread() start; " << "thread id " << this_thread::get_id() << endl;

	std::chrono::milliseconds dura(5000);
	std::this_thread::sleep_for(dura);
	cout << "mythread() end " << "thread id = " << this_thread::get_id() << endl;

	return 5;
}

class A{

public:
	int mythread2(int temp){
		cout << "mythread2() start, thread id : " << this_thread::get_id() << endl;
		std::chrono::milliseconds dura(5000);
		std::this_thread::sleep_for(dura);
		cout << "mythread2() end, thread id : " << this_thread::get_id() << endl;
		return temp;
	}


private:


};

void mythread3(std::promise<int> &tempp, int calc){
	cout << "mythread() start" << "thread id : " << this_thread::get_id() << endl;
	calc++;
	// time for calc
	std::chrono::milliseconds dura(2000);
	this_thread::sleep_for(dura);
	
	int result = calc;
	tempp.set_value(result);
	cout << "mythread() end, thread id : " << this_thread::get_id() << endl;

	return;
}

void mythread4(std::future<int> &tempf){
	auto result = tempf.get();
	cout << "mythread4 result = " << result << endl;
	return;
}
void mythread5(std::promise<int> &tempp, int i){
	i++;
	tempp.set_value(i);
}
void mythread6(std::future<int>& tempfu){
	auto result = tempfu.get();
	cout << result << endl;
}

int main(){
	/*
	cout << "main thread id " << this_thread::get_id() << endl;
	std::future<int> result = std::async(mythread);

	cout << "continue..." << endl;
	cout << result.get() << endl;

	cout << "main 主函数执行结束" << endl;
	*/
//
//	A a;
//	int b = 10;
//	std::future<int> result = std::async(std::launch::async, &A::mythread2, &a, b);
//	cout << "main thread start, thread id : " << this_thread::get_id() << endl;
//	cout << result.get() << endl;
//

//
//	cout << "main" << "thread id = " std::this_thread::get_id() <<endl;
//
//	std::packaged_task<int<int>> mypt(mthread);
//	std::thread t1(std::ref(mypt), 1);
//	t1.join();
//

	cout << "main" << "thread id = " << std::this_thread::get_id() << endl;

	std::promise<int> myprom;	
	std::thread t1(mythread3, std::ref(myprom), 180);
	t1.join();

	std::future<int> fu1 = myprom.get_future();
	std::thread t2(mythread4, std::ref(fu1));
	t2.join();

	std::promise<int> myprom2;
	std::thread t3(mythread5, std::ref(myprom2), 2);
	t3.join();

	std::future<int> fu2 = myprom2.get_future();
//	cout << fu2.get() << endl;
//	cout << "main thread end " << endl;
//
	std::thread t4(mythread6, std::ref(fu2));
	t4.join();



	return 0;
}
