#include <iostream>


using namespace std;


namespace first
{
	int x = 1;
	int y = 2;

}


namespace second
{
	double x = 3.3;
	double y = 4.4;
	class Test1
	{
	public:
		Test1()
		{
			std::cout << "Test1()" << std::endl;
		}
		int v1_test1;
	};
namespace thrid
{
	double z = 5.5;
	double i = 6.6;
	class Test2 : public Test1
	{
		public:
		Test2()
		{
			cout << "Test2()" << endl;
		}

		void operator()()
		{
			cout << "Test2()::operator()()" << endl;
		}
	};
	Test1 t1;
	// std::cout << t1.v1_test1 << std::endl;
	// x = 7.7;

}

}

int main(){

	second::thrid::Test2 test2;
	// 这个只是声明了一个返回类型为second::thrid::Test2 的函数
	second::thrid::Test2 test22();
	test2();

	return 0;
}
