#define TEST_MACRO_
#define MAX_NUM(a, b) (((a) > (b)) ? (a) : (b))
#include <iostream>

using namespace std;
int main(){
	int i = 0;	
	int j = 1;

#ifdef TEST_MACRO
	std::cout << "define TEST_MACRO " << endl;
#else
	std::cout << "not define TEST_MACRO" << endl;
#endif

#ifdef MAX_NUM
	std::cout << MAX_NUM(i, j) << std::endl;

#endif
	

	return 0;
}
