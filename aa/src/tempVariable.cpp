#include <iostream>
#include <memory>

class A{
public:
	A(){}

	virtual ~A(){}
	int i = 0;
};


int main(){
	{
	std::shared_ptr<A> a = std::make_shared<A>();
	}
	//std::cout << a->i << std::endl;

	return 0;
}
