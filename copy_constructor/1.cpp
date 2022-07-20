#include <iostream>

using namespace std;

class B{};

class A
{
public:
	A(){}

	int GetI(){

		return i_;
	}

	void SetI(int i ){
		i_ = i;
	}

private:
	int i_;
};


int main()
{
	A a1;
	a1.SetI(1);
	std::cout << "a1 i : " << a1.GetI() << std::endl;
	A a2(a1);
	std::cout << "a2 i : " << a2.GetI() << std::endl;


	return 0;
}
