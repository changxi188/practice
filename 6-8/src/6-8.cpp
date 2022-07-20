#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;

class A{

public:
	void inMsgRecvQueue(){
		for(int i = 0; i < 100000; ++i){
			cout << "inMsgRecvQueue() start, insert a data" << i << endl;
			unique_lock<mutex> sbguard1(mymutex);
			msgRecvQueue.push_back(i);
			my_cond.notify_all();
		}
		return ;
	}

	bool outMsgLULProc(int& command){
		if(!msgRecvQueue.empty()){
			std::unique_lock<mutex> sbguard1(mymutex);
			if (!msgRecvQueue.empty()){

				command = msgRecvQueue.front();
				msgRecvQueue.pop_front();
				return true;
			}
		}
		return false;

	}
//	void outMsgRecvQueue(){ 
//		int command = 0;
//		int i = 0;	
//		//for(int i = 0; i < 10000; ++i){
//		while(1){
//			bool result = outMsgLULProc(command);
//			if (result){
//				cout  << "outMsgRecvQueue()  start, take a data from queue" << command << endl;
//			}
//			else{
//				cout << "outMsgRecvQueue() start, queue is empty" << endl;
//			}
//			++i;
//		}
//		cout << "endl" << endl;
//	
//	}
//	

	void outMsgRecvQueue(){
		int command = 0;
		while(1){
			unique_lock<mutex> sbguard1(mymutex);
			my_cond.wait(sbguard1, [this]{
				if(!msgRecvQueue.empty())
					return true;
				return false;
			});
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			cout << "outMsgRecvQueue() start, take a data from queue " << command << ", threadid = "  << this_thread::get_id() << endl;
			// ..... others;
		}

	}
	
private:
	list<int> msgRecvQueue;
	std::mutex mymutex;
	std::condition_variable  my_cond;
};




int main(){


	A myobja;
	thread mytInMsgObj(&A::inMsgRecvQueue, &myobja);
	thread mytOutMsgObj(&A::outMsgRecvQueue, &myobja);
	thread mytOutMsgObj2(&A::outMsgRecvQueue, &myobja);

	mytInMsgObj.join();
	mytOutMsgObj.join();
	mytOutMsgObj2.join();

	cout << "Main endl " << endl;


	return 0;
}

