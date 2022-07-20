#include <iostream>
#include <memory>


using namespace std;


template<typename T>
class A
{
public:
	A(T i, T j);

	void test();

	virtual ~A()
	{

		std::cout << "~A() start" << std::endl;
	}


private:
	T a_i_;
	T a_j_;
};

template<typename T>
void A<T>::test(){

	std::cout << "A : test" << std::endl;
}


template<typename T>
class B : public A<T>
{
public:
	B(T i);

	~B()
	{
		std::cout << "~B() start" << std::endl;
	}

private:
	T b_i_;
	T b_j_;
};


template<typename T>
A<T>::A(T i, T j)
{
	a_i_ = i;
	a_j_ = j;

	std::cout << "A() start" << std::endl;
}

template<typename T>
B<T>::B(T i) : A<T>(i, i), b_i_(i), b_j_(i)
{
	std::cout << "B() start" << std::endl;
};


int main(){

	/*
	int *a = new int(10);

	std::cout << *a << std::endl;

	A<int> a2(10, 11);
	std::shared_ptr<A<int>> a3(new A<int>(10, 11));

	std::shared_ptr<A<int>> a4 = std::make_shared<A<int>>(10, 11);
	*/

	// std::shared_ptr<B<int>> b1 = std::make_shared<B<int>>(10);
	
	// std::shared_ptr<A<int>> b2 = std::make_shared<B<int>>(11);

	// A<int>* a1(new A<int>(1, 2));
	// a1->test();


	// delete a;
	// delete a1;
	//
	A<int>* a(new B<int>(1));


	delete a;
	return 0;

}
