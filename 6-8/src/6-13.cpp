#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <future>
#include <list>


using namespace std;


class A{
public:
	void inMsgRecvQueue(){
		for(int i = 0; i < 10000; ++i){
			unique_lock<mutex> sbguard(my_mutex);
			msgRecvQueue.push_back(i);
			my_cond.notify_one();
			cout << "inMsgRecvQueue() start, push a data" << i << endl;
		}
	
	}

	void outMsgRecvQueue(){
		int command = 0;
		//for(int i = 0; i < 10000; ++i){
		while(true){
			unique_lock<mutex> sbguard(my_mutex);
			my_cond.wait(sbguard, [this]{
				if(!msgRecvQueue.empty())
					return true;
				return false;
			});

			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			sbguard.unlock();
			cout << "outMsgRecvQueue() start, take a data : " << command << endl;
		}
	
	}

private:
	std::mutex my_mutex;
	std::condition_variable my_cond;
	list<int> msgRecvQueue;

};


int main(){

	A myobja;
	thread mytobj1(&A::inMsgRecvQueue, &myobja);
	thread mytobj2(&A::outMsgRecvQueue, &myobja);

	mytobj1.join();
	mytobj2.join();
	return 0;
}

