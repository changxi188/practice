#include <iostream>
#include <string>
#include <vector>
#include <thread>


using namespace std;


// 自己创建的线程也要从函数(初始函数)开始运行
void myprint(){
	
	cout << "thread1 start" << endl;

		cout << "thread1 start" << endl;

	cout << "thread1 end" << endl;
cout << "thread1 end" << endl;
	cout << "thread1 start" << endl;

	cout << "thread1 end" << endl;

}

// 用类创建子线程
class TA{
public:
	
	int myi;

	// 构造函数
	TA(const int &i) : myi(i) {
	
		cout << "构造函数被执行" << endl;
	}

	// 拷贝构造函数
	TA(const TA &ta) : myi(ta.myi) {
		cout << "拷贝构造函数被执行" << endl;
	}

	// 析构函数
	~TA(){
		cout << "析构函数被执行" << endl;
	}


	// operator() 使得类变成可调用对象
	void operator() (){
		cout << "thread class start" << endl;

		cout << "thread class end" << endl;
	}


};
int main(){

	//(1.1) thread: 是一个标准库中的类
	//(1.2) join(): 加入/汇合, 说白了就是阻塞, 阻塞主线程,主线程等待子线程执行完毕
	// 一般传统方法中主线程要等待子线程执行完毕才结束,不然容易报错

	//(1.3) detach(): 分离, 也就是主线程和子线程不再汇合, 主线程与子线程之间失去关联, 此时子线程驻留在后台运行, 子线程被C++运行时库接管程当子线程运行完成, 由运行时库负责清理该线程相关资源(守护线程)
	// detach() 使线程myprint失去我们自己的控制

	//(1.4) joinable() : 判断是否可以成功使用join()或者detach()的, 返回bool值

	thread mytobj(myprint);	//(1)创建了线程, 线程执行起点(入口)myprint();	(2)myprint线程开始执行
	
	if (mytobj.joinable()){
		//mytobj.join(); // 主线程阻塞道这里等待myprint()执行完毕, 当子线程执行完毕,这个join()就执行完毕, 这时候主线程开始执行
	} else{
		cout << "cannot joinable thread" << endl;
	}
	//mytobj.detach; // 一旦调用detach(),就不能再调用join(),否则系统会报错
	
	int myi = 6;
	TA ta(myi);
	thread mytobj3(ta);
	if(mytobj3.joinable()){
		//mytobj3.join();
	}

	mytobj3.join();
	mytobj.join();
	cout << "I love c++" << endl;

	


	return 0;

}
