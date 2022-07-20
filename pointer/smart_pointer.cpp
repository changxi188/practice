#include <memory>
#include <iostream>

using namespace std;

class Base
{
public:
	Base(int i);
	~Base(){
		std::cout << "~Base() start" << std::endl;
	};

private:
	int b_i_;

};

Base::Base(int i) : b_i_(i)
{
	std::cout << "Base(int i) start " << std::endl;
}


class Derive : public Base
{
public:
	Derive(int i, int j) : Base(i), d_j_(j){
		std::cout << "Derive(int i, int j) start" << std::endl;
	}

	~Derive()
	{
		std::cout << "~Derive() start" << std::endl;
	}


private:
	int d_i_;
	int d_j_;

};


int main(){

	// std::shared_ptr<Base> d1 = std::make_shared<Derive>(1, 2);
	// Base* d1(new Derive(1, 2));
	std::shared_ptr<Base> d2(new Derive(1, 2));

	// delete d1;
	return 0;
}
