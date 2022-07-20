#include <iostream>
#include "template_class.h"


using namespace std;


template<typename T>
A<T>::A(){
	m_a = 1;
	m_b = 2;
}

template<typename T>
void A<T>::Test(){

	std::cout << "test template " << std::endl;
}

int main(){

	A<int> a;

	std::cout << a.m_a << std::endl;

}



