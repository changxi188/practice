#include <iostream>
#include <functional>


using namespace std;


void CallBackFunc(){

	std::cout << "CallBackFunc start" << std::endl;

}


void CallBackFunc2(){



	std::cout << "CallBackFunc2 start" << std::endl;
}


int CallBackFunc3(int a){


	std::cout <<  "self plus one : " << ++a << std::endl;

	return a;
}



template<typename T>
class A{
public:
	A();

	T Add(T m_i, T m_j);
private:
	T m_i;
	T m_j;

};


template<typename T>
A<T>::A(){}

template<typename T>
T A<T>::Add(T m_i, T m_j){

	return m_i + m_j;

}

int main(){

	std::cout << CallBackFunc << std::endl;
	std::cout << CallBackFunc2 << std::endl;
	std::function<void()> f1 = CallBackFunc;
	f1();
	std::function<void()> f2 = CallBackFunc2;
	f2();


	std::function<int(int)> f3 = CallBackFunc3;
	int x = f3(3);
	std::cout << x << std::endl;


	A<int> a;
	std::function<int(int, int)> f4 = std::bind(&A<int>::Add, &a, std::placeholders::_1, std::placeholders::_2);
	std::cout << f4(1, 2) << std::endl;

	return 0;
}
