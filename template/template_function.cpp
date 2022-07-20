#include <iostream>



using namespace std;



template<typename T>
void Swap(T& a, T& b){
	T c;
	c = a;
	a = b;
	b = c;	
}

int main(){

	int i_a = 1;
	int i_b = 2;

	Swap(i_a, i_b);
	std::cout << i_a <<" " << i_b << std::endl;

	double d_a = 1.1;
	double d_b = 2.2;
	Swap<double>(d_a, d_b);

	std::cout << d_a <<" " << d_b << std::endl;




	return 0;
}
