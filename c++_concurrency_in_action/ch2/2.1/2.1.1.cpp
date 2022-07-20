#include <iostream>
#include <thread>


using namespace std;


void do_something(const int& i){
	// cout << i << endl;
}

class func{
public:
	func(int& i) : i_(i) {}

	void operator()(){
		for(int j = 0; j < 100; ++j){
			do_something(i_);
		}
		cout << std::this_thread::get_id() << endl;
	}

private:
	int& i_;
};

class thread_guard1{
public:
	explicit thread_guard1(std::thread& t_) : t(t_) {};
	~thread_guard1(){
		if(t.joinable()){
			t.join();
		}
	}
	thread_guard1(const thread_guard1&) = delete;
	thread_guard1& operator=(const thread_guard1&) = delete;
private:
	std::thread& t;

};

void oops(){
	int i = 0;
	func f1(i);
	thread t1(f1);
	thread_guard1 g(t1);
	do_something(100);
}

int main(){


	oops();

	cout << "main : " <<  std::this_thread::get_id() << endl;
}
