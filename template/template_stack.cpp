#include "template_stack.h"

#include <iostream>



template <typename T, int MAX_SIZE>
Stack<T, MAX_SIZE>::Stack(){
	data_.reserve(MAX_SIZE);
	std::cout << "Stack<T, MAX_SIZE>() start" << std::endl;
}

template<typename T, int MAX_SIZE>
void Stack<T, MAX_SIZE>::push(const T& temp){
	data_.push_back(temp);
}

template<typename T, int MAX_SIZE>
T Stack<T, MAX_SIZE>::pop(){
	auto end = data_.back();
	data_.pop_back();
	return end;
}

using namespace std;

int main(){

	Stack<int, 20> s1;

	s1.push(1);
	s1.push(2);


	std::cout << s1.pop() << std::endl;

	return 0;
}
