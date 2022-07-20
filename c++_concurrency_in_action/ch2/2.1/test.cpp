#include <iostream>
#include <memory>


using namespace std;

class A{
public:
	typedef std::shared_ptr<A> Ptr;
	A(int& i) : i_(i){
		std::cout << "A(int& i) start " << std::endl;
	}

	int GetI(){
		return i_;
	}

	~A(){
		std::cout << "~A() start " << std::endl;
	}

private:
	int& i_;
};

int main(){
	int local_var = 0;
	A a1(local_var);
	cout << a1.GetI() << endl;;
	local_var = 1;
	cout << a1.GetI() << endl;;
	// a.GetI();

	A::Ptr a_p = std::make_shared<A>(local_var);
	cout <<a_p->GetI() << endl;;
	local_var = 2;
	cout << a1.GetI() << endl;;
	cout <<a_p->GetI() << endl;;


	return 0;
}
