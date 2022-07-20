#ifndef TEMPLATE_STACK_H_
#define TEMPLATE_STACK_H_

#include <vector>
template<typename T, int MAX_SIZE>
class Stack{
public:
	Stack();

	void push(const T& temp);

	T pop();

public:
	std::vector<T> data_;
	
};


#endif
